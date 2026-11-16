#include "Car.h"

static auto const cWheelSize = 632;

Car::Car(IWheelSpeedSensor::UPtr sensor) :
	MotorVehicle{ std::move(sensor), cWheelSize}
{
}
