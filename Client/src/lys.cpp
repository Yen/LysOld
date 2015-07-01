#include "lys.hpp"

#include <chrono>
#include <sstream>
#include <iomanip>

std::string lysDateTime(const std::string &format)
{
	std::stringstream output;
	time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	output << std::put_time(std::localtime(&time), format.data());
	return output.str();
}