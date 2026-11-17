#include "Car.h"

static size_t const cWheelSize = 632;

Car::Car(IWheelSpeedSensor::UPtr sensor) :
	MotorVehicle{ std::move(sensor), cWheelSize}
{
}
