#include "pixmap.hpp"

#include <FreeImage.h>
#include <sstream>

namespace lys
{

	Pixmap::Information::Information()
	{}

	Pixmap::Information::Information(const Metric2 &size, const Format &format, const Depth &depth)
		: size(size), format(format), depth(depth)
	{}

	bool Pixmap::Information::operator ==(const Information &other) const
	{
		return((size == other.size) && (format == other.format) && (depth == other.depth));
	}

	bool Pixmap::Information::operator !=(const Information &other) const
	{
		return !(*this == other);
	}

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

		_information.size.x = FreeImage_GetWidth(dib);
		_information.size.y = FreeImage_GetHeight(dib);
		_information.depth = FreeImage_GetBPP(dib);

		auto format = FreeImage_GetColorType(dib);
		switch (format)
		{
		case FIC_RGB:
			_information.format = Information::Format::RGB;
			break;
		case FIC_RGBALPHA:
			_information.format = Information::Format::RGBA;
			break;
		default:
			std::stringstream err;
			err << "Unsupported image color format (" << path << ")";
			throw std::exception(err.str().data());
		}

		int size = (_information.size.x * _information.size.y) * (_information.depth / 8);

		_data.resize(size);
		memcpy(_data.data(), FreeImage_GetBits(dib), size);

		FreeImage_Unload(dib);
	}

	const std::vector<unsigned char> &Pixmap::getData() const
	{
		return _data;
	}

	const Pixmap::Information &Pixmap::getInformation() const
	{
		return _information;
	}

}