/**
 * @file main.cpp
 * @authors
 *      Jefferson Lopes (jefferson.lopes@ee.ufcg.edu.br)
 * @brief Send message to the server to test the server response
 * @version 1.1
 * @date 2023-09-02
 *
 * @copyright Copyright (c) 2023
 *
 * Version   Modified By   Date        Comments
 * -------  -------------  ----------  -----------
 *  1.0.0    Jefferson L.  31/08/2023  add hello world in esp-idf
 *  1.1.0    Jefferson L.  02/09/2023  send random number soil humidity and temperature
 */

#include <inttypes.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_random.h"
#include "sdkconfig.h"

static const char* TAG = "send_server";

void app_main(void) {
    ESP_LOGW(TAG, "Send Server");

    /* Print chip information */
    esp_chip_info_t chip_info;
    uint32_t flash_size;
    esp_chip_info(&chip_info);
    printf("This is %s chip with %d CPU core(s), %s%s%s%s, ", CONFIG_IDF_TARGET, chip_info.cores,
           (chip_info.features & CHIP_FEATURE_WIFI_BGN) ? "WiFi/" : "", (chip_info.features & CHIP_FEATURE_BT) ? "BT" : "",
           (chip_info.features & CHIP_FEATURE_BLE) ? "BLE" : "",
           (chip_info.features & CHIP_FEATURE_IEEE802154) ? ", 802.15.4 (Zigbee/Thread)" : "");

    unsigned major_rev = chip_info.revision / 100;
    unsigned minor_rev = chip_info.revision % 100;
    printf("silicon revision v%d.%d, ", major_rev, minor_rev);


    if (esp_flash_get_size(NULL, &flash_size) != ESP_OK) {
        printf("Get flash size failed");
        return;
    }
    printf("%" PRIu32 "MB %s flash\n", flash_size / (uint32_t)(1024 * 1024),
           (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    printf("Minimum free heap size: %" PRIu32 " bytes\n", esp_get_minimum_free_heap_size());

    uint16_t random_uint, last_uint=50;
    float random_float, last_float=25;

    while (true) {
        // Generate a random number between 0 and 100
        random_uint = esp_random() % 101; // Modulo 101 to get values between 0 and 100
        random_uint = (int)((last_uint * 0.9) + (random_uint * 0.1));
        last_uint = random_uint;
        printf("SOIL:%u\n", random_uint);

        // Generate a random float number between 0 and 50
        random_float = (float)esp_random() / UINT32_MAX * 50.0;
        random_float = (last_float * 0.9) + (random_float * 0.1);
        last_float = random_float;
        printf("TEMP:%.2f\n", random_float);
        
        fflush(stdout);

        vTaskDelay(15000 / portTICK_PERIOD_MS); // 15000 ms delay

        /// Generate a random number between 0 and 100
        random_uint = esp_random() % 101; // Modulo 101 to get values between 0 and 100
        random_uint = (int)((last_uint * 0.9) + (random_uint * 0.1));
        last_uint = random_uint;
        printf("SOIL:%u\n", random_uint);

        // Generate a random float number between 0 and 50
        random_float = (float)esp_random() / UINT32_MAX * 50.0;
        random_float = (last_float * 0.9) + (random_float * 0.1);
        last_float = random_float;
        printf("TEMP:%.2f\n", random_float);
        
        fflush(stdout);

        vTaskDelay(15000 / portTICK_PERIOD_MS); // 15000 ms delay
    }
}