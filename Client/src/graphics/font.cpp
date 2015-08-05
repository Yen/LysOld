#include "font.hpp"

#include <sstream>

#include "..\utils.hpp"

namespace lys
{

	Font &Font::getDefaultFont()
	{
		static Font instance(LYS_DEFAULT_FONT);
		return instance;
	}

	FT_Library &Font::getLibraryInstance()
	{
		static FT_Library instance;
		if (instance == nullptr)
		{
			if (FT_Init_FreeType(&instance))
			{
				throw std::exception("Error initializing freetype library");
			}
		}
		return instance;
	}

	Font::Font(const std::string &path)
		: Font(path, LYS_DEFAULT_FONT_HEIGHT)
	{}

	Font::Font(const std::string &path, const FT_UInt &height)
		: _facePath(path), _height(height)
	{
		setFacePath(_facePath);
		setHeight(_height);
	}

	Font::~Font()
	{
		FT_Done_Face(_face);
	}

	const FT_GlyphSlot &Font::getFTGlyph() const
	{
		return _glyph;
	}

	void Font::loadCharacter(const FT_ULong &code)
	{
		FT_Load_Glyph(_face, FT_Get_Char_Index(_face, code), FT_LOAD_RENDER);
	}

	void Font::setHeight(const FT_UInt &height)
	{
		_height = height;
		FT_Set_Pixel_Sizes(_face, 0, _height);
	}

	const FT_UInt &Font::getHeight() const
	{
		return _height;
	}

	void Font::setFacePath(const std::string &path)
	{
		_facePath = path;

		if (_face != nullptr)
		{
			FT_Done_Face(_face);
		}

		if (FT_New_Face(getLibraryInstance(), _facePath.data(), 0, &_face))
		{
			std::stringstream ss;
			ss << "Error creating font (" << _facePath << ")";
			throw std::exception(ss.str().data());
		}

		_glyph = _face->glyph;
	}

	const std::string &Font::setFacePath() const
	{
		return _facePath;
	}

}