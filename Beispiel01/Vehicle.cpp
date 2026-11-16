#include "Vehicle.h"

void Vehicle::Register(IVehicleListener::UPtr listener)
{
	mListeners.emplace_back(std::move(listener));
}

void Vehicle::Notify() const
{
	for (auto const& elem : mListeners)
	{
		elem->Update();
	}
}
