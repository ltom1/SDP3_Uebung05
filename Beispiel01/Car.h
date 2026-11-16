#ifndef CAR_H
#define CAR_H

#include "MotorVehicle.h"

/// @author Philip Ackermann
/// @date 16.11.2026
/// @brief A car whith a concrete wheel diameter
class Car : public MotorVehicle
{
public:
	/// @brief CTor of car
	/// @param[in] sensor The senor te car is equipped with
	Car(IWheelSpeedSensor::UPtr sensor);

};

#endif