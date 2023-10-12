#include "../include/moist_sensor.h"

esp_adc_cal_characteristics_t adc2_chars;

uint32_t moist_sensor_read(){
    int adc_value;
    esp_err_t err = adc2_get_raw(ADC2_CHANNEL_0,  ADC_WIDTH_BIT_12 , &adc_value);
    return(esp_adc_cal_raw_to_voltage(adc_value, &adc2_chars));
}


void moist_sensor_init(){
    esp_adc_cal_characterize(ADC_UNIT_2, ADC_ATTEN_DB_11 , ADC_WIDTH_BIT_DEFAULT, 0, &adc2_chars);
    adc2_config_channel_atten(ADC2_CHANNEL_0, ADC_ATTEN_DB_11  );
}

double moist_sensor_percentage(uint32_t moist_sensor_value){
    double range = MOIST_SENSOR_MAX_VALUE - MOIST_SENSOR_MIN_VALUE;
    double distance = moist_sensor_value - MOIST_SENSOR_MIN_VALUE;
    double percentage = (distance / range) * 100;
    
    return((percentage == -0) ? -percentage : percentage);
}