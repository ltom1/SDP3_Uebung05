#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H

#include "ISpeedProvider.h"
#include "IVehicleListener.h"
#include "Display.h"


/// @author Thomas Lechner
/// @date 15.11.2026
/// @brief Speedometer that visualizes the current speed of a ISpeedProvider.
/// 
/// Visualizes the speed using an AnalogDisplay.
class Speedometer : public Display, public IVehicleListener
{
public:
	/// @brief CTor.
	/// @param[in] provider The ISpeedProvider the Speedometer gets the speed from.
	Speedometer(ISpeedProvider::SPtr const& provider);

	/// @brief Notification method, when speed data changes.
	void Update() override;

private:
	/// @brief The source of the speed values.
	ISpeedProvider::WPtr mProvider;
};

#endif