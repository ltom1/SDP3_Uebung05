#include "gtest/gtest.h"

#include "WheelSpeedSimulator.h"
#include "Speedometer.h"
#include "KilometerCounter.h"
#include "ISpeedProvider.h"
#include "Car.h"


//////////////////////////////////////////

TEST(WheelSpeedSimulator, DoesNotExist) {

	try {
		WheelSpeedSimulator const sim{ "DoesNotExist.txt" };
		FAIL();
	}
	catch (std::runtime_error const& ex) {
		EXPECT_STREQ(ex.what(), "Could not open file!");
	}
}

TEST(WheelSpeedSimulator, Test) {

	WheelSpeedSimulator sim{ "LinearRevs.txt" };

	for (size_t i = 1; i <= 20; ++i)
	{
		EXPECT_EQ(sim.GetRevolutions(), i);
	}

	EXPECT_EQ(sim.GetRevolutions(), 0);
	EXPECT_EQ(sim.GetRevolutions(), 0);
	EXPECT_EQ(sim.GetRevolutions(), 0);
}

TEST(WheelSpeedSimulator, InvalidFileFormat) {

	WheelSpeedSimulator sim{ "InvalidRevs.txt" };

	for (size_t i = 0; i < 10; ++i)
	{
		try {
			sim.GetRevolutions();
			FAIL();
		}
		catch (std::runtime_error const& ex) {
			EXPECT_STREQ(ex.what(), "Invalid file format!");
		}
	}
	EXPECT_EQ(sim.GetRevolutions(), (std::numeric_limits<size_t>::max)()); // One single valid entry.

	EXPECT_EQ(sim.GetRevolutions(), 0);
	EXPECT_EQ(sim.GetRevolutions(), 0);
	EXPECT_EQ(sim.GetRevolutions(), 0);
}

//////////////////////////////////////////

TEST(Speedometer, Test) {
	class SpeedSim : public ISpeedProvider
	{
	public:
		double GetCurrentSpeed() const {
			static double speed = 0.0;
			speed += 10;
			return speed;
		}
	};

	Speedometer speedometer{ std::make_shared<SpeedSim>() };

	for (size_t i = 0; i < 10; ++i) {
		speedometer.Update();
		Sleep(500);
	}
}

//////////////////////////////////////////

TEST(KilometerCounter, Test) {
	class SpeedSim: public ISpeedProvider
	{
	public:
		double GetCurrentSpeed() const {
			return 3600; // Full speed: 1km/s.
		}
	};

	KilometerCounter counter{ std::make_shared<SpeedSim>() };

	for (size_t i = 0; i < 20; ++i) {
		counter.Update();
		Sleep(500);
	}
}

//////////////////////////////////////////

TEST(Car, Test) {
	auto speedSensor = std::make_unique<WheelSpeedSimulator>("RealisticRevs.txt");
	auto  car1 = std::make_shared<Car>(std::move(speedSensor));

	auto counter = std::make_unique<KilometerCounter>(car1);
	auto speedometer = std::make_unique<Speedometer>(car1);

	car1->Register(std::move(counter));
	car1->Register(std::move(speedometer));

	

	for (size_t i = 0; i < 55; ++i) {
		car1->Process();
		Sleep(500);
	}

}