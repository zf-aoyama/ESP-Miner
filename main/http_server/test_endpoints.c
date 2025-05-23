#include "cJSON.h"
#include "esp_http_server.h"
#include "esp_log.h"
#include "test_mode.h"

static const char * TAG = "test_api";
static GlobalState * s_state = NULL;

// Forward declarations from http_server.c
extern esp_err_t is_network_allowed(httpd_req_t * req);
extern esp_err_t set_cors_headers(httpd_req_t * req);

static esp_err_t start_handler(httpd_req_t * req)
{
    if (is_network_allowed(req) != ESP_OK) {
        return httpd_resp_send_err(req, HTTPD_401_UNAUTHORIZED, "Unauthorized");
    }
    set_cors_headers(req);
    test_mode_start(TEST_MODE_RUNNING);
    httpd_resp_sendstr(req, "{\"status\":\"started\"}");
    return ESP_OK;
}

static esp_err_t stop_handler(httpd_req_t * req)
{
    set_cors_headers(req);
    test_mode_stop();
    httpd_resp_sendstr(req, "{\"status\":\"stopped\"}");
    return ESP_OK;
}

static esp_err_t options_handler(httpd_req_t * req)
{
    set_cors_headers(req);
    httpd_resp_send(req, NULL, 0);
    return ESP_OK;
}

static esp_err_t status_handler(httpd_req_t * req)
{
    set_cors_headers(req);
    TestModule tm;
    test_mode_get_status(&tm);
    cJSON * root = cJSON_CreateObject();
    cJSON_AddBoolToObject(root, "active", tm.active);
    cJSON_AddNumberToObject(root, "mode", tm.mode);
    char * resp = cJSON_Print(root);
    httpd_resp_sendstr(req, resp);
    cJSON_free(resp);
    cJSON_Delete(root);
    return ESP_OK;
}

static esp_err_t results_handler(httpd_req_t * req)
{
    set_cors_headers(req);
    // TODO: return actual results
    httpd_resp_sendstr(req, "{\"results\":\"not_implemented\"}");
    return ESP_OK;
}

esp_err_t register_test_api_endpoints(httpd_handle_t server, void * ctx)
{
    s_state = (GlobalState *) ctx;
    httpd_uri_t start = {.uri = "/api/test/start", .method = HTTP_POST, .handler = start_handler, .user_ctx = NULL};
    httpd_uri_t stop = {.uri = "/api/test/stop", .method = HTTP_POST, .handler = stop_handler, .user_ctx = NULL};
    httpd_uri_t status = {.uri = "/api/test/status", .method = HTTP_GET, .handler = status_handler, .user_ctx = NULL};
    httpd_uri_t results = {.uri = "/api/test/results", .method = HTTP_GET, .handler = results_handler, .user_ctx = NULL};
    httpd_uri_t options = {.uri = "/api/test/*", .method = HTTP_OPTIONS, .handler = options_handler, .user_ctx = NULL};
    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &start));
    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &stop));
    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &status));
    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &results));
    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &options));
    return ESP_OK;
}
