#include "esp_log.h"
#include "test_mode.h"

void test_log(const char * msg)
{
    ESP_LOGI("test_utils", "%s", msg);
}
