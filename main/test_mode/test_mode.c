#include "test_mode.h"
#include "esp_log.h"

static const char * TAG = "test_mode";
static TestModule s_test_module = {0};
static GlobalState * s_state = NULL;

esp_err_t test_mode_init(GlobalState * state)
{
    if (!state) {
        return ESP_ERR_INVALID_ARG;
    }
    s_state = state;
    s_test_module.active = false;
    s_test_module.mode = TEST_MODE_IDLE;
    s_test_module.last_result = ESP_OK;
    return ESP_OK;
}

esp_err_t test_mode_start(test_mode_t mode)
{
    if (!s_state) {
        return ESP_ERR_INVALID_STATE;
    }
    if (s_test_module.active) {
        return ESP_ERR_INVALID_STATE;
    }
    s_test_module.active = true;
    s_test_module.mode = mode;
    ESP_LOGI(TAG, "Starting test mode %d", mode);
    // TODO: implement actual tests
    s_test_module.last_result = ESP_OK;
    return ESP_OK;
}

esp_err_t test_mode_stop(void)
{
    if (!s_test_module.active) {
        return ESP_ERR_INVALID_STATE;
    }
    s_test_module.active = false;
    s_test_module.mode = TEST_MODE_IDLE;
    ESP_LOGI(TAG, "Test mode stopped");
    return ESP_OK;
}

esp_err_t test_mode_get_status(TestModule * out)
{
    if (!out)
        return ESP_ERR_INVALID_ARG;
    *out = s_test_module;
    return ESP_OK;
}
