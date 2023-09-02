/**
 * @file main.c
 * @authors
 *      Felipe
 *      Jefferson Lopes (jefferson.lopes@ee.ufcg.edu.br)
 *      Yanis
 * @brief Smart Garden's embedded firmware
 * @version 1.0
 * @date 2023-09-02
 *
 * @copyright Copyright (c) 2023
 *
 * Version   Modified By   Date        Comments
 * -------  -------------  ----------  -----------
 *  1.0.0    Jefferson L.  02/09/2023  create template
 */

#include <inttypes.h>
#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_err.h"
#include "esp_log.h"

#include "sdkconfig.h"

static const char* TAG = "firmware";

// prototypes
esp_err_t config_soil();
esp_err_t read_soil(uint16_t*);
esp_err_t config_temp();
esp_err_t read_temp(float*);

void app_main() {
    esp_log_level_set(TAG, ESP_LOG_DEBUG);
    ESP_LOGW(TAG, "Smart Garden's embedded firmware");

    uint16_t soil;
    float temp;

    ESP_ERROR_CHECK(config_soil());
    ESP_ERROR_CHECK(config_temp());

    while (true) {
        // read and check soil
        if (read_soil(&soil) == ESP_OK) {
            printf("SOIL:%u\n", soil);
        }
        else {
            printf("DEBUG:error reading soil sensor\n");
            ESP_LOGE(TAG, "error reading soil sensor");
        }
        
        // read and check temperature
        if (read_temp(&temp) == ESP_OK) {
            printf("TEMP:%.2f\n", temp);
        }
        else {
            printf("DEBUG:error reading temperature sensor\n");
            ESP_LOGE(TAG, "error reading temperature sensor");
        }

        fflush(stdout);
        vTaskDelay(5000 / portTICK_PERIOD_MS); // 15000 ms delay
    }
}

esp_err_t config_soil() {
    // do some configuration

    return ESP_OK;
}

esp_err_t read_soil(uint16_t *pointer_soil) {
    // soil reading routine
    *pointer_soil = 50;

    if (false) { // if error on the reading
        return ESP_ERR_NOT_FINISHED;
    }

    // if success
    return ESP_OK;
}

esp_err_t config_temp() {
    // do some configuration

    return ESP_OK;
}

esp_err_t read_temp(float *pointer_temp) {
    // temperature reading routine
    *pointer_temp = 25.3;

    if (false) { // if error on the reading
        return ESP_ERR_NOT_FINISHED;
    }

    // if success
    return ESP_OK;
}