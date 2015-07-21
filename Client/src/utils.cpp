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

		MeshData loadMeshOBJ(const std::string &path)
		{
			MeshData result;

			/*result.vertices.push_back(MeshData::MeshDataVertex{ Vector3(0, 0, 0), Vector3(0, 0, 0), Vector2(0, 0) });
			result.vertices.push_back(MeshData::MeshDataVertex{ Vector3(1, 0, 0), Vector3(0, 0, 0), Vector2(1, 0) });
			result.vertices.push_back(MeshData::MeshDataVertex{ Vector3(1, 1, 0), Vector3(0, 0, 0), Vector2(1, 1) });

			result.indices.push_back(0);
			result.indices.push_back(1);
			result.indices.push_back(2);*/

			struct FaceInfo
			{
				unsigned short vertexIndex[3];
				unsigned short normalIndex[3];
				unsigned short coordIndex[3];
			};

			std::vector<Vector3> vertices;
			std::vector<Vector3> normals;
			std::vector<Vector2> coords;

			std::vector<FaceInfo> faces;

			std::string data = readFile(path);
			std::istringstream in(data);
			std::string line;

			while (std::getline(in, line))
			{
				std::istringstream buffer(line);
				std::istream_iterator<std::string> start(buffer), end;

				std::deque<std::string> tokens(start, end);

				if (tokens.empty()) continue;

				std::string &type = tokens.front();

				if (type == "v")
				{
					Vector3 result;
					tokens.pop_front();
					std::istringstream buffer(tokens.front());
					buffer >> result.x;

					tokens.pop_front();
					buffer = std::istringstream(tokens.front());
					buffer >> result.y;

					tokens.pop_front();
					buffer = std::istringstream(tokens.front());
					buffer >> result.z;

					vertices.push_back(result);
				}
				else if (type == "vn")
				{
					Vector3 result;
					tokens.pop_front();
					std::istringstream buffer(tokens.front());
					buffer >> result.x;

					tokens.pop_front();
					buffer = std::istringstream(tokens.front());
					buffer >> result.y;

					tokens.pop_front();
					buffer = std::istringstream(tokens.front());
					buffer >> result.z;

					normals.push_back(result);
				}
				else if (type == "vt")
				{
					Vector2 result;
					tokens.pop_front();
					std::istringstream buffer(tokens.front());
					buffer >> result.x;

					tokens.pop_front();
					buffer = std::istringstream(tokens.front());
					buffer >> result.y;

					coords.push_back(result);
				}
				else if (type == "f")
				{
					tokens.pop_front();
					FaceInfo result;

					for (unsigned char i = 0; i < 3; i++)
					{
						std::string ver;
						std::string tex;
						std::string nor;

						std::string &working = tokens.front();

						size_t offset = working.find('/');
						ver = working.substr(0, offset);

						working = working.substr(ver.size() + 1, working.size() - ver.size());

						offset = working.find('/');
						tex = working.substr(0, offset);

						working = working.substr(tex.size() + 1, working.size() - tex.size());

						nor = working;

						if (!ver.empty())
						{
							std::istringstream buffer(ver);
							buffer >> result.vertexIndex[i];
							result.vertexIndex[i]--;
						}

						if (!nor.empty())
						{
							std::istringstream buffer(nor);
							buffer >> result.normalIndex[i];
							result.normalIndex[i]--;
						}

						if (!tex.empty())
						{
							std::istringstream buffer(tex);
							buffer >> result.coordIndex[i];
							result.coordIndex[i]--;
						}

						tokens.pop_front();
					}

					faces.push_back(result);
				}
			}

			// how 2 data

			for (unsigned short i = 0; i < faces.size(); i++)
			{
				FaceInfo &working = faces[i];

				for (unsigned char c = 0; c < 3; c++)
				{
					Vector3 pos;
					Vector3 nor;
					Vector2 cor;
					if (!vertices.empty())
					{
						pos = vertices[working.vertexIndex[c]];
					}
					if (!normals.empty())
					{
						nor = normals[working.normalIndex[c]];
					}
					if (!coords.empty())
					{
						cor = coords[working.coordIndex[c]];
					}
					result.vertices.push_back(MeshData::MeshDataVertex{ pos, nor, cor });
					result.indices.push_back((i * 3) + c);
				}
			}

			return result;
		}

	}

}