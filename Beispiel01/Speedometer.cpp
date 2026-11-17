#include "Speedometer.h"

static auto const cErrNullptr = "Provided ISpeedProvider is nullptr!";

Speedometer::Speedometer(ISpeedProvider::SPtr const& provider) :
	mProvider{ provider },
	Display{ std::make_unique<AnalogDisplay>() }
{
	if (mProvider.expired()) throw std::invalid_argument(cErrNullptr);
}

void Speedometer::Update()
{
	if (auto const& provider = mProvider.lock())
	{
		double const speed = provider->GetCurrentSpeed();
		// Clamp value to max if it exceeds unsigned int limit.
		mDisplay->SendValue(speed < UINT_MAX ? static_cast<unsigned int>(std::round(speed)) : UINT_MAX);
	}
	else
	{
		throw std::runtime_error(cErrNullptr);
	}
}
