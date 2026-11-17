#ifndef DISPLAY_H
#define DISPLAY_H

#include "Object.h"
#include "WindowsDisplay.h"


/// @author Thomas Lechner
/// @date 15.11.2026
/// @brief Abstract base class for all classes that visualize data using a WindowsDisplay member.
class Display : public Object
{
protected:
	/// @brief CTor.
	/// @param[in] display The WindowsDisplay the class should use to visualize its data.
	Display(std::unique_ptr<WindowsDisplay> display);
	
	/// @brief WindowsDisplay member.
	std::unique_ptr<WindowsDisplay> mDisplay;
};
#endif