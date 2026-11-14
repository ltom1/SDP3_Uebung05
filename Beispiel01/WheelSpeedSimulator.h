#ifndef IWHEELSPEEDSIMULATOR_H
#define IWHEELSPEEDSIMULATOR_H

#include "IWheelSpeedSensor.h"
#include "Object.h"

#include <string>
#include <fstream>


/// @author Thomas Lechner
/// @date 14.11.2026
/// @brief Provides simulated wheel rotation speeds.
/// 
/// Reads the values from a file.
class WheelSpeedSimulator : public Object, public IWheelSpeedSensor
{
public:
	/// @brief CTor.
	/// @param[in] filename The file name of the file where the rpm data is read from.
	///
	/// Opens the file.
	WheelSpeedSimulator(std::string const& filename);

	/// @brief DTor.
	///
	/// Closes the file.
	~WheelSpeedSimulator();

	/// @brief Gets the current wheel rotations per minute.
	/// @returns The measured wheel revolutions or 0 if we ran out of data.
	size_t GetRevolutions() override;

private:
	/// @brief File stream of the rpm data file.
	std::ifstream mFile;
};

#endif