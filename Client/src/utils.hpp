#pragma once

#include <GL\glew.h>
#include <FreeImage.h>

#include "lys.hpp"

namespace lys
{

	namespace utils
	{

		std::string readFile(const std::string &path);

		BYTE *loadImage(const std::string &path, GLsizei *width, GLsizei *height, unsigned int *bits);

	}

}