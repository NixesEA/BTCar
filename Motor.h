#ifndef Motor_h
#define Motor_h
#include <Arduino.h>

#define FORWARD		0
#define BACKWARD	1
#define STOP		2

class Motor
{
  public:
	Motor(uint8_t dig_pin, uint8_t pwm_pin);
	
	void setSpeed(uint16_t duty);
	
	void setMode(uint8_t mode);

	void setDirection(boolean direction);
	
  private:
	void rideForward();
	void rideBackward();
	uint8_t _dig_pin = 0, _pwm_pin = 0, _mode = 0;
	int16_t _duty = 0;
};

#endif