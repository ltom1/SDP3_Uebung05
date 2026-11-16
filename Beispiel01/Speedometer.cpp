#include "Speedometer.h"

static auto const cErrNullptr = "Provided ISpeedProvider is nullptr!";

Speedometer::Speedometer(ISpeedProvider::SPtr provider) :
	mProvider{ std::move(provider) },
	Display{ std::make_unique<AnalogDisplay>() }
{
	if (mProvider == nullptr) throw std::invalid_argument(cErrNullptr);
}

void Speedometer::Update()
{
	double const speed = mProvider->GetCurrentSpeed();
	// Clamp value to max if it exceeds unsigned int limit.
	mDisplay->SendValue(speed < UINT_MAX ? static_cast<unsigned int>(std::round(speed)) : UINT_MAX);
}
