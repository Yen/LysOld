#pragma once

#include "pixmap.hpp"

#include <GL/glew.h>

namespace lys
{

	class Texture2D
	{
		friend class FrameBuffer;
	private:
		GLuint _id;
		Pixmap::Information _information;
	public:
		Texture2D(const Pixmap &pixmap);
		Texture2D(const unsigned char *data, const Pixmap::Information &information);
		~Texture2D();

		void setData(const unsigned char *data, const Pixmap::Information &information);

		const Pixmap::Information &getPixmapInformation() const;

		void bind() const;
		static void unbind();
	private:
		void writeData(const unsigned char *data);
	};

}