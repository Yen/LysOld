#include "utils.hpp"

#include <fstream>
#include <sstream>

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
			char *data = new char[length + 1];
			memset(data, 0, length + 1);
			fseek(file, 0, SEEK_SET);
			fread(data, 1, length, file);
			fclose(file);

			std::string result(data);
			delete[] data;
			return result;
		}

	}

}