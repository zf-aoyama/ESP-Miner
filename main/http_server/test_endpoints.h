#ifndef TEST_ENDPOINTS_H
#define TEST_ENDPOINTS_H

#include "esp_http_server.h"
#include "global_state.h"

esp_err_t register_test_api_endpoints(httpd_handle_t server, void * ctx);

#endif // TEST_ENDPOINTS_H
