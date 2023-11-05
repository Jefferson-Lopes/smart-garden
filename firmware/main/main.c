#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "string.h"
#include "esp_system.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "driver/uart.h"

#include "../include/ds18b20.h" //Include library
#include "../include/moist_sensor.h"
#include "../include/motor.h"
#include "../include/serial.h"

const static char *TAG = "SADI";

const int DS_PIN = 16; // GPIO where you connected ds18b20

void app_main()
{
    moist_sensor_init();
    ds18b20_init(DS_PIN);
    motor_init();
    serial_init();
    int voltage;
    float temp;
    float moist;
    uint8_t data;

    motor_control(true);
    vTaskDelay(pdMS_TO_TICKS(500));
    motor_control(false);

    while (1)
    {
        voltage = moist_sensor_read();
        moist = moist_sensor_percentage(voltage);
        printf("SOIL:%.1f\n", moist);
        
        temp = ds18b20_get_temp();
        printf("TEMP:%.1f\n", temp);

        fflush(stdout);

        vTaskDelay(pdMS_TO_TICKS(1000));

        if (uart_read_bytes(UART_NUM_0, &data, 1, 1) == 1) {
            if (data == 's') {
                ESP_LOGW(TAG, "motor turned on");
                motor_control(true);
                vTaskDelay(pdMS_TO_TICKS(500));
                motor_control(false);
                ESP_LOGW(TAG, "motor turned off");
            }
            else {
                ESP_LOGE(TAG, "unknow char %c", data);
            }
        }
    }
}
