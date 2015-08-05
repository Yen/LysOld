#pragma once

#include <string>
#include <exception>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace lys
{

#define LYS_DEFAULT_FONT			"data/fonts/OpenSans-Regular.ttf"
#define LYS_DEFAULT_FONT_HEIGHT		48

	class Font
	{
	private:
		FT_Face _face;
		FT_GlyphSlot _glyph;
		FT_UInt _height;
		std::string _facePath;
	private:
		static FT_Library &getLibraryInstance();
	public:
		static Font &getDefaultFont();
	public:
		Font(const std::string &path);
		Font(const std::string &path, const FT_UInt &height);
		~Font();

		const FT_GlyphSlot &getFTGlyph() const;
		void loadCharacter(const FT_ULong &code);

		void setHeight(const FT_UInt &height);
		const FT_UInt &getHeight() const;

		void setFacePath(const std::string &path);
		const std::string &setFacePath() const;
	};

}