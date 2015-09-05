#include "typeengine.hpp"

#include <sstream> 

#include "..\..\lys.hpp"

namespace lys
{

	TypeEngine::TypeEngine()
	{
		if (FT_Init_FreeType(&_library) != 0)
		{
			throw std::exception("Error initializing FreeType library");
		}
	}

	TypeEngine::~TypeEngine()
	{
		FT_Done_FreeType(_library);
	}

	Glyph TypeEngine::getGlyph(const wchar_t character, const unsigned int height, const std::string &faceName)
	{
		FT_Face &face = getFace(faceName);
		FT_Set_Pixel_Sizes(face, 0, height);
		FT_Load_Glyph(face, FT_Get_Char_Index(face, character), FT_LOAD_DEFAULT);

		FT_Glyph glyph;
		FT_Get_Glyph(face->glyph, &glyph);
		FT_Glyph_To_Bitmap(&glyph, FT_RENDER_MODE_NORMAL, nullptr, true);
		FT_BitmapGlyph bitmap = reinterpret_cast<FT_BitmapGlyph>(glyph);

		Glyph result{ Glyph::Bitmap{ bitmap->bitmap.buffer, bitmap->bitmap.width, bitmap->bitmap.rows, bitmap->left, bitmap->top }, Vector2{ (float)(face->glyph->advance.x >> 6), (float)(face->glyph->advance.y >> 6) } };
		return result;
	}

	bool TypeEngine::loadFace(const std::string &name, const std::string &path, const FT_Long &index)
	{
		if (getFace(name) != nullptr)
		{
			LYS_LOG_ERR("Attempted to load a type face (%s)[%s] where (%s) is already occupied", name.data(), path.data(), name.data());
			return false;
		}

		FT_Face face = nullptr;
		if (FT_New_Face(_library, path.data(), index, &face) != 0)
		{
			std::stringstream ss;
			ss << "Error initializing type face (" << path << ")";
			throw std::exception(ss.str().data());
		}

		if (face == nullptr)
		{
			std::stringstream ss;
			ss << "Type face (" << name << ") was initialized but pointer was null";
			throw std::exception(ss.str().data());
		}
		_faces[name] = face;
		return true;
	}

	bool TypeEngine::unloadFace(const std::string &name)
	{
		if (_faces[name] == nullptr)
		{
			LYS_LOG_ERR("Attempted to unload type face (%s) that was not present", name.data());
			return false;
		}
		_faces.erase(name);
		return true;
	}

	FT_Face &TypeEngine::getFace(const std::string &name)
	{
		return _faces[name];
	}

}