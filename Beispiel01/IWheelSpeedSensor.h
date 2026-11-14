#ifndef IWHEELSPEEDSENSOR_H
#define IWHEELSPEEDSENSOR_H

#include <memory>


/// @author Thomas Lechner
/// @date 14.11.2026
/// @brief Common interface class for all wheel speed sensors.
class IWheelSpeedSensor
{
public:
	/// @brief std::unique_ptr of this class.
	using UPtr = std::unique_ptr<IWheelSpeedSensor>;

	/// @brief Gets the current wheel rotations per minute.
	/// @returns The measured wheel revolutions.
	virtual size_t GetRevolutions() = 0;

	/// @brief Virtual DTor.
	virtual ~IWheelSpeedSensor() = default;
};

#endif