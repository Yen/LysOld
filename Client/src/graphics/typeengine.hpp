#pragma once

#include <list>
#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_STROKER_H

#include "..\maths.hpp"

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

	class TypeEngine;

	class TypeFace
	{
		friend class TypeEngine;
	private:
		FT_Face _face;
		FT_Glyph _glyph = nullptr;
		bool _libraryLoaded;
		TypeEngine &_typeEngine;
	public:
		TypeFace(TypeEngine &typeEngine, const std::string &path, const long &faceIndex = 0);
		~TypeFace();

		unsigned int getCharacterIndex(const wchar_t &character) const;
		bool containsCharacter(const wchar_t &character) const;
	private:
		void setHeight(const unsigned int &height);
		void loadGlyph(const long &index);
		FT_Glyph &getGlyph();
	};

	class TypeStroke
	{
		friend class TypeEngine;
	private:
		FT_Stroker _stroker;
		long _radius;
		bool _libraryLoaded;
		TypeEngine &_typeEngine;
	public:
		TypeStroke(TypeEngine &typeEngine, const long &radius = 0);
		~TypeStroke();

		const long &getRadius() const;
		void setRadius(const long &radius);
	private:
		void apply(FT_Glyph &glyph);
	};

	class TypeEngine
	{
		friend class TypeFace;
		friend class TypeStroke;
	private:
		FT_Library _library;
		std::list<TypeFace *> _faces;
		std::list<TypeStroke *> _strokes;
		TypeFace _default;
	public:
		TypeEngine();
		~TypeEngine();

		Glyph getGlyph(const wchar_t &character, const unsigned int &height, TypeFace &face, TypeStroke *stroke = nullptr);
		TypeFace &getDefault();
	};

}