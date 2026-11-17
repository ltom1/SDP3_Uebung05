#include "gtest/gtest.h"

#include <vld.h>

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

TEST(WheelSpeedSimulator, EmptyFile) {

	WheelSpeedSimulator sim{ "EmptyRevs.txt" };

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
	auto const sim = std::make_shared<SpeedSim>();

	Speedometer speedometer{ sim };

	for (size_t i = 0; i < 10; ++i) {
		speedometer.Update();
		Sleep(500);
	}
}

TEST(Speedometer, Nullptr) {
	class SpeedSim : public ISpeedProvider
	{
	public:
		double GetCurrentSpeed() const {
			return 3600; // Full speed: 1km/s.
		}
	};

	try {
		Speedometer const speedometer{ nullptr };
		FAIL();
	}
	catch (std::invalid_argument const& ex) {
		EXPECT_STREQ(ex.what(), "Provided ISpeedProvider is nullptr!");
	}

	Speedometer speedometer{ std::make_shared<SpeedSim>() };
	try {
		speedometer.Update();
		FAIL();
	}
	catch (std::runtime_error const& ex)
	{
		EXPECT_STREQ(ex.what(), "Provided ISpeedProvider is nullptr!");
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

	auto const sim = std::make_shared<SpeedSim>();

	KilometerCounter counter{ sim };

	for (size_t i = 0; i < 20; ++i) {
		counter.Update();
		Sleep(500);
	}
}

TEST(KilometerCounter, Nullptr) {
	class SpeedSim : public ISpeedProvider
	{
	public:
		double GetCurrentSpeed() const {
			return 3600; // Full speed: 1km/s.
		}
	};

	try {
		KilometerCounter const counter{ nullptr };
		FAIL();
	}
	catch (std::invalid_argument const& ex) {
		EXPECT_STREQ(ex.what(), "Provided ISpeedProvider is nullptr!");
	}

	KilometerCounter counter{ std::make_shared<SpeedSim>() };
	try {
		counter.Update();
		FAIL();
	}
	catch (std::runtime_error const& ex)
	{
		EXPECT_STREQ(ex.what(), "Provided ISpeedProvider is nullptr!");
	}
}

//////////////////////////////////////////

TEST(Car, IntegrationTest) {
	auto speedSensor = std::make_unique<WheelSpeedSimulator>("RealisticRevs.txt");
	auto const car1 = std::make_shared<Car>(std::move(speedSensor));

	auto counter = std::make_unique<KilometerCounter>(car1);
	auto speedometer = std::make_unique<Speedometer>(car1);

	car1->Register(std::move(counter));
	car1->Register(std::move(speedometer));

	for (size_t i = 0; i < 55; ++i) {
		car1->Process();
		Sleep(500);
	}

}

TEST(Car, noSensor) {


	try {
		Car const car(nullptr); // make a car with no wheel speed sensor
		EXPECT_EQ(1, 0); // did not catch exeption
	}
	catch (std::invalid_argument const& ex) {
		
		EXPECT_STREQ(ex.what(), "Provided WheelSpeedSensor is nullptr!"); // catched exeption
	}

}

TEST(Car, noListener) {

	auto speedSensor = std::make_unique<WheelSpeedSimulator>("RealisticRevs.txt");
	Car car(std::move(speedSensor));

	try {
		car.Register(nullptr); // register a non existent display
		EXPECT_EQ(1, 0); // did not catch exeption
	}
	catch (std::invalid_argument const& ex) {

		EXPECT_STREQ(ex.what(), "Attached listener is nullptr!"); // catched exeption
	}

}