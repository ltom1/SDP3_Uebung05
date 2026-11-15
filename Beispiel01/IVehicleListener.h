#ifndef IVEHICLELISTENER_H
#define IVEHICLELISTENER_H

#include <memory>


/// @author Thomas Lechner
/// @date 15.11.2026
/// @brief Interface class for observers of Vehicle.
class IVehicleListener
{
public:
	/// @brief std::unique_ptr of this class.
	using UPtr = std::unique_ptr<IVehicleListener>;

	/// @brief Notification method, when data changes inside the Vehicle.
	virtual void Update() = 0;

	/// @brief Virtual DTor.
	virtual ~IVehicleListener() = default;
};

#endif