
#include "Motor.h"
#include <Arduino.h>

Motor::Motor(uint8_t dig_pin, uint8_t pwm_pin) {
	_dig_pin = dig_pin;
	_pwm_pin = pwm_pin;
	
	pinMode(_dig_pin, OUTPUT);
	pinMode(_pwm_pin, OUTPUT);
	digitalWrite(_dig_pin, 0);
	digitalWrite(_pwm_pin, 0);
}

void Motor::setSpeed(uint16_t duty) {
	_duty = duty;
	if (_mode == FORWARD) {
		rideForward();
	}else if (_mode == BACKWARD) {
		rideBackward();
	} else if (_mode == STOP) {
		digitalWrite(_pwm_pin, 0);
	}		
}

void Motor::rideForward() {
	digitalWrite(_dig_pin, 0);
	analogWrite(_pwm_pin, _duty);
}
void Motor::rideBackward() {
	digitalWrite(_dig_pin, 1);
	analogWrite(_pwm_pin, 255 - _duty);
}

void Motor::setMode(uint8_t mode) {
	_mode = mode;
	if (mode == STOP) {
		digitalWrite(_dig_pin, 0);
		digitalWrite(_pwm_pin, 0);
	}
}