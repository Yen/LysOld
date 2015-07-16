#include "texture.hpp"

#include <sstream>

#include "..\utils.hpp"

namespace lys
{

	Texture::Texture(const std::string &path, const GLenum &min, const GLenum &mag, const GLenum &wrapS, const GLenum &wrapT)
	{
		GLsizei width, height;
		BYTE *pixels = utils::loadImage(path, &width, &height, &_bits);

		glGenTextures(1, &_id);
		glBindTexture(GL_TEXTURE_2D, _id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);

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

	Texture::Texture(const std::string &path)
		: Texture(path, GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE)
	{}

	Texture::Texture(const Metric2 &size)
	{
		glGenTextures(1, &_id);

		glBindTexture(GL_TEXTURE_2D, _id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
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

	const GLuint &Texture::getID() const
	{
		return _id;
	}

}