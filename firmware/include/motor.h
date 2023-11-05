#ifndef MOTOR_H
#define MOTOR_H

#include "driver/gpio.h"

void motor_init();

void motor_control(bool);

#endif // MOTOR_H