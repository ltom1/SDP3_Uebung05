#include "Display.h"

static auto const cErrNullptr = "Provided WindowsDisplay is nullptr!";

Display::Display(std::unique_ptr<WindowsDisplay> display) :
	mDisplay{ std::move(display) }
{
	if (mDisplay == nullptr) throw std::invalid_argument(cErrNullptr);
}