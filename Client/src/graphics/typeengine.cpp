#include "typeengine.hpp"

#include <sstream> 
#include <boost/filesystem.hpp>

#include "..\lys.hpp"

namespace lys
{

#pragma region Face

	TypeEngine::Face::Face(TypeEngine &typeEngine, const std::string &path, const long &faceIndex)
		: _typeEngine(typeEngine)
	{
		if (FT_New_Face(typeEngine._library, path.data(), faceIndex, &_face) != 0)
		{
			std::stringstream ss;
			ss << "Error creating FreeType type face (" << path << ")";
			throw std::exception(ss.str().data());
		}
		typeEngine._faces.push_back(this);
		_libraryLoaded = true;
	};

	TypeEngine::Face::~Face()
	{
		if (_libraryLoaded)
		{
			FT_Done_Glyph(_glyph);
			FT_Done_Face(_face);
			_typeEngine._faces.remove(this);
		}
	}

	unsigned int TypeEngine::Face::getCharacterIndex(const wchar_t &character) const
	{
		return FT_Get_Char_Index(_face, character);
	}

	bool TypeEngine::Face::containsCharacter(const wchar_t &character) const
	{
		return getCharacterIndex(character) != 0;
	};

	void TypeEngine::Face::setHeight(const unsigned int &height)
	{
		FT_Set_Pixel_Sizes(_face, 0, height);
	}

	void TypeEngine::Face::loadGlyph(const long &index)
	{
		FT_Load_Glyph(_face, index, FT_LOAD_DEFAULT);
	}

	FT_Glyph &TypeEngine::Face::getGlyph()
	{
		FT_Done_Glyph(_glyph);
		FT_Get_Glyph(_face->glyph, &_glyph);
		return _glyph;
	}

#pragma endregion Face

#pragma region Stroke

	TypeEngine::Stroke::Stroke(TypeEngine &typeEngine, const long &radius)
		: _radius(radius), _typeEngine(typeEngine)
	{
		if (FT_Stroker_New(typeEngine._library, &_stroker) != 0)
		{
			throw std::exception("Error creating FreeType stroker");
		}
		setRadius(_radius);
		typeEngine._strokes.push_back(this);
		_libraryLoaded = true;
	}

	TypeEngine::Stroke::~Stroke()
	{
		if (_libraryLoaded)
		{
			FT_Stroker_Done(_stroker);
			_typeEngine._strokes.remove(this);
		}
	}

	const long &TypeEngine::Stroke::getRadius() const
	{
		return _radius;
	}

	void TypeEngine::Stroke::setRadius(const long &radius)
	{
		_radius = radius;
		FT_Stroker_Set(_stroker, _radius, FT_STROKER_LINECAP_ROUND, FT_STROKER_LINEJOIN_ROUND, 0);
	}

	void TypeEngine::Stroke::apply(FT_Glyph &glyph)
	{
		FT_Glyph_StrokeBorder(&glyph, _stroker, false, true);
	}

#pragma endregion Stroke

	TypeEngine::TypeEngine()
	{
		if (FT_Init_FreeType(&_library) != 0)
		{
			throw std::exception("Error initializing FreeType library");
		}

#define LYS_TYPEENGINE_DEFAULT_FONT "data/core/defaultfonts/NotoSans-Regular.ttf"

		_defaultFaces.push_back(std::make_unique<Face>(*this, LYS_TYPEENGINE_DEFAULT_FONT));
		_defaultFace = _defaultFaces[0].get();

		using namespace boost::filesystem;

		for (directory_iterator i(path("data/core/defaultfonts/other")); i != directory_iterator(); i++)
		{
			_defaultFaces.push_back(std::make_unique<Face>(*this, i->path().string()));
		}
	}

	TypeEngine::~TypeEngine()
	{
		for (auto &face : _faces)
		{
			face->_libraryLoaded = false;
		}
		for (auto &stroke : _strokes)
		{
			stroke->_libraryLoaded = false;
		}

		FT_Done_FreeType(_library);
	}

	TypeEngine::Glyph TypeEngine::getGlyph(const wchar_t &character, const unsigned int &height, Face *face, Stroke *stroke)
	{
		Face *buf = face;
		if (buf == nullptr || !buf->containsCharacter(character))
		{
			for (auto &f : _defaultFaces)
			{
				if (!f->containsCharacter(character))
					continue;
				buf = f.get();
				break;
			}
			if (buf == nullptr)
				buf = _defaultFace;
		}
		buf->setHeight(height);
		buf->loadGlyph(buf->getCharacterIndex(character));

		FT_Glyph &glyph = buf->getGlyph();

		if (stroke != nullptr)
		{
			stroke->apply(glyph);
		}

		FT_Glyph_To_Bitmap(&glyph, FT_RENDER_MODE_NORMAL, nullptr, true);
		FT_BitmapGlyph bitmap = reinterpret_cast<FT_BitmapGlyph>(glyph);

		Glyph result{ Glyph::Bitmap{ bitmap->bitmap.buffer, bitmap->bitmap.width, bitmap->bitmap.rows, bitmap->left, bitmap->top }, Vector2{ (float)(buf->_face->glyph->advance.x >> 6), (float)(buf->_face->glyph->advance.y >> 6) } };
		return result;
	}

	//TypeEngine::Face &TypeEngine::getDefault()
	//{
	//	return _default;
	//}

}