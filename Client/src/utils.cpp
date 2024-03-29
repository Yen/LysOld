#include "utils.hpp"

#include <fstream>
#include <sstream>
#include <iterator>

namespace lys
{

	namespace utils
	{

		std::string readFile(const std::string &path)
		{
			FILE *file = fopen(path.data(), "rt");
			if (file == nullptr)
			{
				std::stringstream err;
				err << "Failed to read file (" << path << ")";
				throw std::exception(err.str().data());
			}
			fseek(file, 0, SEEK_END);
			long length = ftell(file);
			std::vector<char> data(length + 1);
			memset(data.data(), 0, length + 1);
			fseek(file, 0, SEEK_SET);
			fread(data.data(), 1, length, file);
			fclose(file);

			std::string result(data.data());
			return result;
		}

		std::vector<BYTE> loadImage(const std::string &path, GLsizei *width, GLsizei *height, unsigned int *bits)
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

			BYTE *pixels = FreeImage_GetBits(dib);
			*width = FreeImage_GetWidth(dib);
			*height = FreeImage_GetHeight(dib);
			*bits = FreeImage_GetBPP(dib);

			int size = *width * *height * (*bits / 8);
			std::vector<BYTE> result(size);
			memcpy(result.data(), pixels, size);
			FreeImage_Unload(dib);
			return result;
		}

	}

}