#include "typeface.hpp"

#include <sstream>

namespace lys
{

	TypeFace &TypeFace::instance()
	{
		static TypeFace instance(TypeLibrary::instance(), LYS_TYPEFACE_DEFAULT_PATH);
		return instance;
	}

	TypeFace::TypeFace(TypeLibrary &library, const std::string &path)
	{
		if (FT_New_Face(library._library, path.data(), 0, &_face) != 0)
		{
			std::stringstream ss;
			ss << "Error initializing TypeFace (" << path << ")";
			throw std::exception(ss.str().data());
		}
	}

	TypeFace::~TypeFace()
	{
		FT_Done_Face(_face);
	}

	void TypeFace::loadCharacter(const wchar_t &character)
	{
		FT_Load_Glyph(_face, FT_Get_Char_Index(_face, character), FT_LOAD_RENDER);
	}

	void TypeFace::setHeight(const unsigned int &height)
	{
		_height = height;
		FT_Set_Pixel_Sizes(_face, 0, _height);
	}

	const unsigned int &TypeFace::getHeight() const
	{
		return _height;
	}

	const Glyph &TypeFace::getGlyph() const
	{
		return _face->glyph;
	}

}