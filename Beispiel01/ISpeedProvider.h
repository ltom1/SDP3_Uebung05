#ifndef ISPEEDPROVIDER_H
#define ISPEEDPROVIDER_H

#include <memory>


/// @author Thomas Lechner
/// @date 15.11.2026
/// @brief Interface for classes that provide a speed value.
class ISpeedProvider
{
public:
	/// @brief std::shared_ptr of this class.
	using SPtr = std::shared_ptr<ISpeedProvider>;

	/// @brief std::weak_ptr of this class.
	using WPtr = std::weak_ptr<ISpeedProvider>;
	
	/// @brief Provides the current speed value.
	/// @returns The current speed value.
	virtual double GetCurrentSpeed() const = 0;

	/// @brief Virtual DTor.
	virtual ~ISpeedProvider() = default;
};

#endif