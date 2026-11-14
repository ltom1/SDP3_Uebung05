#include "gtest/gtest.h"

#include "WheelSpeedSimulator.h"


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
	EXPECT_EQ(sim.GetRevolutions(), std::numeric_limits<size_t>::max()); // One single valid entry.

	EXPECT_EQ(sim.GetRevolutions(), 0);
	EXPECT_EQ(sim.GetRevolutions(), 0);
	EXPECT_EQ(sim.GetRevolutions(), 0);
}

//////////////////////////////////////////