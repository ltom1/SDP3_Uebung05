#ifndef VEHICLE_H
#define VEHICLE_H

#include "Object.h"
#include "IVehicleListener.h"

#include <vector>
#include <stdexcept>

/// @author Philip Ackermann
/// @date 16.11.2026
/// @brief Manages diffrent listener of a Vehicle
/// 
/// Can add listeners and notify them all at an event
class Vehicle : public Object
{
public:
	/// @brief Adds a new listener
	/// @param The listener to add
	void Register(IVehicleListener::UPtr listener);

protected:

	/// @brief Notifys all listener to update themselves
	void Notify() const;

	/// @brief CTor of Vehicle
	Vehicle() = default;

private:
	/// @brief A container of all listeners
	std::vector<IVehicleListener::UPtr> mListeners;

};
#endif