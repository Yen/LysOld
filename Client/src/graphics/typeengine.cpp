#include "typeengine.hpp"

#include <sstream> 
#include <algorithm>
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
		: _defaultCache(std::numeric_limits<wchar_t>::max())
	{
		if (FT_Init_FreeType(&_library) != 0)
		{
			throw std::exception("Error initializing FreeType library");
		}

#define LYS_TYPEENGINE_DEFAULT_FONT "data/core/defaultfonts/NotoSans-Regular.ttf"

		_defaultFaces.push_back(std::make_unique<Face>(*this, LYS_TYPEENGINE_DEFAULT_FONT));
		_defaultFace = _defaultFaces[0].get();

		using namespace boost::filesystem;

		auto fontPath = path("data/core/defaultfonts/other");
		if (exists(fontPath))
			for (directory_iterator i(fontPath); i != directory_iterator(); i++)
			{
				_defaultFaces.push_back(std::make_unique<Face>(*this, i->path().string()));
			}

		std::fill(_defaultCache.begin(), _defaultCache.end(), std::pair<Face *, unsigned int>(nullptr, 0));
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
		Face *f = face;
		unsigned int i = 0;
		if ((f == nullptr || !f->containsCharacter(character)) && character != 0)
		{
			auto &buffer = _defaultCache[character];
			if (buffer.first != nullptr)
			{
				f = buffer.first;
				i = buffer.second;
			}
			else
			{
				for (auto &it : _defaultFaces)
				{
					if (!it->containsCharacter(character))
						continue;
					f = it.get();
					i = f->getCharacterIndex(character);
					buffer.first = f;
					buffer.second = i;
					break;
				}
			}
		}
		else
		{
			i = f->getCharacterIndex(character);
		}

		if (f == nullptr)
		{
			f = _defaultFace;
			i = f->getCharacterIndex(character);
		}

		f->setHeight(height);
		f->loadGlyph(i);

		FT_Glyph &glyph = f->getGlyph();

		if (stroke != nullptr)
		{
			stroke->apply(glyph);
		}

		FT_Glyph_To_Bitmap(&glyph, FT_RENDER_MODE_NORMAL, nullptr, true);
		FT_BitmapGlyph bitmap = reinterpret_cast<FT_BitmapGlyph>(glyph);

		Glyph result{ Glyph::Bitmap{ bitmap->bitmap.buffer, bitmap->bitmap.width, bitmap->bitmap.rows, bitmap->left, bitmap->top }, Vector2{ (float)(f->_face->glyph->advance.x >> 6), (float)(f->_face->glyph->advance.y >> 6) } };
		return result;
	}

}