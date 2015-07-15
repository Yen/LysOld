#include "texture.hpp"

#include <sstream>

#include "..\utils.hpp"

namespace lys
{

	Texture::Texture(const std::string &path)
	{
		GLsizei width, height;
		BYTE *pixels = utils::loadImage(path, &width, &height, &_bits);

		glGenTextures(1, &_id);
		glBindTexture(GL_TEXTURE_2D, _id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (_bits != 24 && _bits != 32)
		{
			std::stringstream err;
			err << "Unsupported image bit depth (" << _bits << ")";
			throw std::exception(err.str().data());
		}

		GLuint internalFormat = _bits == 32 ? GL_RGBA : GL_RGB;
		GLuint format = _bits == 32 ? GL_BGRA : GL_BGR;

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);

		glBindTexture(GL_TEXTURE_2D, 0);

		delete[] pixels;
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &_id);
	}

	void Texture::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, _id);
	}

	void Texture::unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}