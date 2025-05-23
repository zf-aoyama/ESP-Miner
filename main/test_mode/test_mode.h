#ifndef TEST_MODE_H
#define TEST_MODE_H

#include "esp_err.h"
#include "global_state.h"

typedef enum
{
    TEST_MODE_IDLE = 0,
    TEST_MODE_RUNNING,
} test_mode_t;

typedef struct
{
    bool active;
    test_mode_t mode;
    esp_err_t last_result;
} TestModule;

esp_err_t test_mode_init(GlobalState * state);
esp_err_t test_mode_start(test_mode_t mode);
esp_err_t test_mode_stop(void);
esp_err_t test_mode_get_status(TestModule * out);

#endif // TEST_MODE_H
