#include "texture2d.hpp"

#include <sstream>

namespace lys
{

	Texture2D::Texture2D(const Pixmap &pixmap)
		: Texture2D(pixmap.getData().data(), pixmap.getInformation())
	{}

	Texture2D::Texture2D(const unsigned char *data, const Pixmap::Information &information)
		: _information(information)
	{
		glGenTextures(1, &_id);

		glBindTexture(GL_TEXTURE_2D, _id);

		//TODO: Custom texture settings
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		//TODO: This fixes errors with small textures like text glyphs.
		//This should be replaced with some maths to check if the width is divisible by a certian number
		//and if not then this should be applied but I am not taking the time to optimise this just yet
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		writeData(data);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &_id);
	}

	void Texture2D::setData(const unsigned char *data, const Pixmap::Information &information)
	{
		_information = information;

		glBindTexture(GL_TEXTURE_2D, 0);

		writeData(data);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	const Pixmap::Information &Texture2D::getPixmapInformation() const
	{
		return _information;
	}

	void Texture2D::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, _id);
	}

	void Texture2D::unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture2D::writeData(const unsigned char *data)
	{
		GLuint internalFormat;
		GLuint format;

		switch (_information.format)
		{
		case Pixmap::Information::Format::ALPHA:
			internalFormat = GL_ALPHA;
			format = GL_ALPHA;
			break;
		case Pixmap::Information::Format::RGB:
			internalFormat = GL_RGB;
			format = GL_BGR;
			break;
		case Pixmap::Information::Format::RGBA:
			internalFormat = GL_RGBA;
			format = GL_BGRA;
			break;
		default:
			//This should never be reached and will probably be removed in release builds
			//(not that it would cause a performance problem anyway)
			std::stringstream err;
			err << "Pixmap format (" << _information.format << ") is not supported by Texture2D";
			throw std::exception(err.str().data());
		}

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, _information.size.x, _information.size.y, 0, format, GL_UNSIGNED_BYTE, data);
	}

}