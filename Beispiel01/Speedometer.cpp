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
	mDisplay->SendValue(mProvider->GetCurrentSpeed());
}
