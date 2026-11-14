#include "WheelSpeedSimulator.h"

#include <charconv>

static auto const cErrFileOpen = "Could not open file!";
static auto const cErrFileRead = "Could not read file!";

static auto const cErrFormat   = "Invalid file format!";

static int const DECIMAL_BASE = 10;

static size_t const DEFAULT_REVS = 0;

WheelSpeedSimulator::WheelSpeedSimulator(std::string const& filename) :
	mFile(filename)
{
	if (!mFile.is_open()) throw std::runtime_error(cErrFileOpen);
}

WheelSpeedSimulator::~WheelSpeedSimulator()
{
	mFile.close();
}

size_t WheelSpeedSimulator::GetRevolutions()
{
	if (!mFile.is_open()) throw std::runtime_error(cErrFileOpen); // Should not happen.

	if (mFile.eof()) return DEFAULT_REVS;

	std::string line = "";
	if (!std::getline(mFile, line)) throw std::runtime_error(cErrFileRead);

	size_t revs = 0;
	// Used to parse the size_t and disallow spaces.
	auto [ptr, ec] = std::from_chars(line.data(), line.data() + line.size(), revs);

	// No range errors, all chars read from the line.
	if (ec != std::errc{} || ptr != line.data() + line.size()) throw std::runtime_error(cErrFormat);

	return revs;
}
