#include "MotorVehicle.h"
#include <stdexcept>

static auto const cErrNullptr = "Provided WheelSpeedSensor is nullptr!";

static double const cPi = 3.14159265358979323;
static size_t const cMinutesPerHour = 60;
static size_t const cMMPerKM = 1000000;

void MotorVehicle::Process()
{
	mRevs = mWheelSpeedSensor->GetRevolutions();
	Notify();
}

double MotorVehicle::GetCurrentSpeed() const
{
	return (cPi * mRevs * mTireDimension * cMinutesPerHour) / cMMPerKM;
}

MotorVehicle::MotorVehicle(IWheelSpeedSensor::UPtr sensor, size_t const tireDimension) :
	mWheelSpeedSensor { std::move(sensor)},
	mTireDimension {tireDimension }
{
	if (mWheelSpeedSensor == nullptr)
	{
		throw std::invalid_argument(cErrNullptr);
	}
}
