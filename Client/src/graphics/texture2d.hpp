#pragma once

#include "pixmap.hpp"

#include <GL/glew.h>

namespace lys
{

	class Texture2D
	{
	private:
		GLuint _id;
		Pixmap::Information _information;
	public:
		Texture2D(const Pixmap &pixmap);
		Texture2D(const unsigned char *data, const Pixmap::Information &information);
		~Texture2D();

		const Pixmap::Information &getPixmapInformation() const;

		void bind() const;
	};

}