#pragma once

#include <list>
#include <vector>
#include <memory>
#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_STROKER_H

#include "..\maths.hpp"

namespace lys
{

	class TypeEngine
	{
		friend class TypeFace;
	public:
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

		class Stroke
		{
			friend class TypeEngine;
		private:
			FT_Stroker _stroker;
			long _radius;
			bool _libraryLoaded;
			TypeEngine &_typeEngine;
		public:
			Stroke(TypeEngine &typeEngine, const long &radius = 0);
			~Stroke();

			const long &getRadius() const;
			void setRadius(const long &radius);
		private:
			void apply(FT_Glyph &glyph);
		};

		class Face
		{
			friend class TypeEngine;
		private:
			FT_Face _face;
			FT_Glyph _glyph = nullptr;
			bool _libraryLoaded;
			TypeEngine &_typeEngine;
		public:
			Face(TypeEngine &typeEngine, const std::string &path, const long &faceIndex = 0);
			~Face();

			unsigned int getCharacterIndex(const wchar_t &character) const;
			bool containsCharacter(const wchar_t &character) const;
		private:
			void setHeight(const unsigned int &height);
			void loadGlyph(const long &index);
			FT_Glyph &getGlyph();
		};
	private:
		FT_Library _library;
		std::list<Face *> _faces;
		std::list<Stroke *> _strokes;
		std::vector<std::unique_ptr<Face>> _defaultFaces;
		Face *_defaultFace;
	public:
		TypeEngine();
		~TypeEngine();

		Glyph getGlyph(const wchar_t &character, const unsigned int &height, Face *face = nullptr, Stroke *stroke = nullptr);
	};

}