#include "KilometerCounter.h"

static auto const cErrNullptr = "Provided ISpeedProvider is nullptr!";

static double constexpr cTimeDivisor = 2*3600; // Fixed 500 ms period 1/2 * 1/3600.

KilometerCounter::KilometerCounter(ISpeedProvider::SPtr provider) :
	mProvider{ std::move(provider) },
	Display{ std::make_unique<DigitalDisplay>() }
{
	if (mProvider == nullptr) throw std::invalid_argument(cErrNullptr);
}

void KilometerCounter::Update()
{
	// Calculate driven kilometers during the last 500 ms period.
	mKilometers += (mProvider->GetCurrentSpeed()) / cTimeDivisor;

	// Round the value and send it to the display.
	mDisplay->SendValue(static_cast<unsigned int>(std::round(mKilometers)));
}

