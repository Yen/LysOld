#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H
#include <string>

#include "typelibrary.hpp"

namespace lys
{

#define LYS_TYPEFACE_DEFAULT_PATH "data/fonts/OpenSans-Regular.ttf"

	typedef FT_GlyphSlot Glyph;

	class TypeFace
	{
	private:
		FT_Face _face;
		Glyph _glyph;
		unsigned int _height;
	public:
		static TypeFace &instance();
	public:
		TypeFace(TypeLibrary &library, const std::string &path);
		~TypeFace();

		void loadCharacter(const wchar_t &character);

		void setHeight(const unsigned int &height);
		const unsigned int &getHeight() const;

		const Glyph &getGlyph() const;
	};

}