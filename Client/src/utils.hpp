#pragma once

#include <GL\glew.h>
#include <FreeImage.h>
#include <vector>

#include "lys.hpp"

namespace lys
{

	namespace utils
	{

		std::string readFile(const std::string &path);

		std::vector<BYTE> loadImage(const std::string &path, GLsizei *width, GLsizei *height, unsigned int *bits);

	}

}