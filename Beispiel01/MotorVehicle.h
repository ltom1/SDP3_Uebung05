#ifndef MOTORVEHICLE_H
#define MOTORVEHICLE_H

#include "Vehicle.h"
#include "ISpeedProvider.h"
#include "IWheelSpeedSensor.h"


/// @author Philip Ackermann
/// @date 16.11.2026
/// @brief A motor vehicle
/// 
/// Stores data about physical characteristics of a motor vehicle and current conditions
class MotorVehicle : public Vehicle, public ISpeedProvider
{
public:
	/// @brief Update the revolutions of the wheels
	void Process();
	
	/// @brief calculates the current speed of the motor vehicle
	/// @returns the current speed in km/h
	double GetCurrentSpeed() const override;


protected:
	/// @brief CTor of MotorVehicle
	/// @param[in] sensor The wheel speed sensor the motor vehicle uses
	/// @param[in] tireDimension The diameter of the motor vehicle's tires in mm
	MotorVehicle(IWheelSpeedSensor::UPtr sensor, size_t const tireDimension);

private:
	/// @brief The diameter of a tire in mm
	size_t mTireDimension;

	// @brief The revolutions of the wheels
	size_t mRevs = 0;

	/// @brief The sensor that measures the wheel rotation speed
	///
	/// Read out by process
	IWheelSpeedSensor::UPtr mWheelSpeedSensor;

};


#endif