#include "Vehicle.h"

static auto const cErrNullptr = "Attached listener is nullptr!";

void Vehicle::Register(IVehicleListener::UPtr listener)
{
	if (listener == nullptr) throw std::invalid_argument(cErrNullptr);


	mListeners.emplace_back(std::move(listener));
}

void Vehicle::Notify() const
{
	for (auto const& elem : mListeners)
	{
		elem->Update();
	}
}
