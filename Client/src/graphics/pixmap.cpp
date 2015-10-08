#include "pixmap.hpp"

#include <FreeImage.h>
#include <sstream>

namespace lys
{

	Pixmap::Pixmap(const std::string &path)
	{
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP *dib = nullptr;

		fif = FreeImage_GetFileType(path.data(), 0);
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(path.data());
		if (fif == FIF_UNKNOWN)
		{
			std::stringstream err;
			err << "Unknown image format (" << path << ")";
			throw std::exception(err.str().data());
		}

		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, path.data());
		else
		{
			std::stringstream err;
			err << "Unable to read image data (" << path << ")";
			throw std::exception(err.str().data());
		}

		if (dib == nullptr)
		{
			std::stringstream err;
			err << "Error reading image data (" << path << ")";
			throw std::exception(err.str().data());
		}

		_size.x = FreeImage_GetWidth(dib);
		_size.y = FreeImage_GetHeight(dib);
		_depth = FreeImage_GetBPP(dib);

		auto format = FreeImage_GetColorType(dib);
		switch (format)
		{
		case FIC_RGB:
			_format = Format::RGB;
			break;
		case FIC_RGBALPHA:
			_format = Format::RGBA;
			break;
		default:
			std::stringstream err;
			err << "Unsupported image color format (" << path << ")";
			throw std::exception(err.str().data());
		}

		int size = (_size.x * _size.y) * (_depth / 8);

		_data.resize(size);
		memcpy(_data.data(), FreeImage_GetBits(dib), size);

		FreeImage_Unload(dib);
	}

	const Metric2 &Pixmap::getSize() const
	{
		return _size;
	}

	const std::vector<unsigned char> &Pixmap::getData() const
	{
		return _data;
	}

	const Pixmap::Format &Pixmap::getFormat() const
	{
		return _format;
	}

	const Pixmap::Depth &Pixmap::getDepth() const
	{
		return _depth;
	}

}