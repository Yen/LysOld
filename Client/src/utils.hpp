#pragma once

#include <GL\glew.h>
#include <FreeImage.h>

#include "lys.hpp"
#include "graphics\meshbatch.hpp"

namespace lys
{

	namespace utils
	{

		std::string readFile(const std::string &path);

		std::vector<BYTE> loadImage(const std::string &path, GLsizei *width, GLsizei *height, unsigned int *bits);

		MeshData loadMeshOBJ(const std::string &path);

	}

}