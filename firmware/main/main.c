#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "string.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_log.h"

#include "../include/ds18b20.h" //Include library
#include "../include/moist_sensor.h"

const int DS_PIN = 16; // GPIO where you connected ds18b20

void app_main()
{
    moist_sensor_init();
    ds18b20_init(DS_PIN);
    uint32_t voltage;

    while (1)
    {
        voltage = moist_sensor_read();
        printf("Humidy percentage: %.1f %%\n", moist_sensor_percentage(voltage));
        float temp = ds18b20_get_temp();
        printf("Temperature: %f\n", temp);
    }
}