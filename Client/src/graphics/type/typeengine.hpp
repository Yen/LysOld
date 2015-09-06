#pragma once

#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_STROKER_H

#include "..\..\maths.hpp"

namespace lys
{

	class Glyph
	{
	public:
		struct Bitmap
		{
			unsigned char *buffer;
			unsigned int &width;
			unsigned int &height;
			int &left;
			int &top;
		} bitmap;
		Vector2 advance;
	};

	class TypeEngine
	{
	private:
		FT_Library _library;
		FT_Stroker _stroker;
		std::map<std::string, FT_Face> _faces;
	public:
		TypeEngine();
		~TypeEngine();

		Glyph getGlyph(const wchar_t &character, const unsigned int &height, const unsigned int &outline, const std::string &faceName);
		bool loadFace(const std::string &name, const std::string &path, const FT_Long &index);
		bool unloadFace(const std::string &name);
	private:
		FT_Face &getFace(const std::string &name);
	};

}