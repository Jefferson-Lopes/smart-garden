#include "../include/moist_sensor.h"

adc_oneshot_unit_handle_t adc1_handle;

void moist_sensor_init(){
    //-------------ADC1 Init---------------//
    adc_oneshot_unit_init_cfg_t init_config1 = {
        .unit_id = ADC_UNIT_1,
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config1, &adc1_handle));

    //-------------ADC1 Config---------------//
    adc_oneshot_chan_cfg_t config = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = ADC_ATTEN_DB_11,
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1_handle, ADC_CHANNEL_5, &config));
}

int moist_sensor_read(){
    int read;
    ESP_ERROR_CHECK(adc_oneshot_read(adc1_handle, ADC_CHANNEL_5, &read));
    return read;
}

float moist_sensor_percentage(int moist_sensor_value){
    float percentage;

    if (moist_sensor_value > MOIST_SENSOR_MAX_VALUE) {
        percentage = 0.0;
    }
    else if (moist_sensor_value < MOIST_SENSOR_MIN_VALUE) {
        percentage = 100.0;
    }
    else {
        float range = MOIST_SENSOR_MAX_VALUE - MOIST_SENSOR_MIN_VALUE;
        float distance = moist_sensor_value - MOIST_SENSOR_MIN_VALUE;
        percentage = (1 - (distance / range)) * 100;
    }
    
    return percentage;
}