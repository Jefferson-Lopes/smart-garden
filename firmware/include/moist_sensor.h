#include "inttypes.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

#define MOIST_SENSOR_MIN_VALUE 3135.0 // Replace with minimum value
#define MOIST_SENSOR_MAX_VALUE 1650.0 // Replace with maximum value

/* Initialize the moist sensor with the given configuration.
Read the documentation for the pinout
*/
void moist_sensor_init();

/* Return the voltage output from the moist sensor.
Function moist_sensor_read() need to be called before.*/
uint32_t moist_sensor_read();

/* Return moist sensor percentage based on sensor calibration.
Take the voltage return by the function moist_sensor_read()*/
double moist_sensor_percentage(uint32_t moist_sensor_value);