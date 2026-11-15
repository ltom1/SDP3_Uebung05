#ifndef KILOMETERCOUNTER_H
#define KILOMETERCOUNTER_H

#include "ISpeedProvider.h"
#include "IVehicleListener.h"
#include "Display.h"


/// @author Thomas Lechner
/// @date 15.11.2026
/// @brief Class that visualizes the kilometer count of an ISpeedProvider.
/// 
/// Visualizes the kilometers using an DigitalDisplay.
class KilometerCounter : public Display, public IVehicleListener
{
public:
	/// @brief CTor.
	/// @param[in] provider The ISpeedProvider the KilometerCounter gets the speed from.
	KilometerCounter(ISpeedProvider::SPtr provider);

	/// @brief Notification method, when speed data changes.
	///
	/// Updates the kilometer count and sends the information to the DigitalDisplay.
	void Update() override;

private:
	/// @brief The source of the speed values.
	ISpeedProvider::SPtr mProvider;

	/// @brief The driven kilometers.
	double mKilometers = 0.0;
};

#endif