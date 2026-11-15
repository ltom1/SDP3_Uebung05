#ifndef ISPEEDPROVIDER
#define ISPEEDPROVIDER

#include <memory>


/// @author Thomas Lechner
/// @date 15.11.2026
/// @brief Interface for classes that provide a speed value.
class ISpeedPrivider
{
public:
	/// @brief std::unique_ptr of this class.
	using SPtr = std::shared_ptr<ISpeedPrivider>;

	/// @brief Provides the current speed value.
	/// @returns The current speed value.
	virtual size_t GetCurrentSpeed() = 0;

	/// @brief Virtual DTor.
	virtual ~ISpeedPrivider() = default;
};

#endif