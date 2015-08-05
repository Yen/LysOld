#include "label.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H
#include <locale>
#include <codecvt>
#include <algorithm>

#include "..\..\lys.hpp"
#include "..\font.hpp"

namespace lys
{

	Label::Label(const std::string &text, const Vector3 &position)
		: Label(text, position, TypeFace::instance())
	{}

	Label::Label(const std::string &text, const Vector3 &position, TypeFace &font)
		: Label(text, position, Vector4(1, 1, 1, 1), font)
	{}

	Label::Label(const std::string &text, const Vector3 &position, const Vector4 &color, TypeFace &font)
		: _text(text), _position(position), _color(color), _font(font)
	{
		repaint();
	}

	void Label::setText(const std::string &text)
	{
		_text = text;

		repaint();
	}

	const std::string &Label::getText() const
	{
		return _text;
	}

	void Label::setFont(TypeFace &font)
	{
		_font = font;

		repaint();
	}

	TypeFace &Label::getFont() const
	{
		return _font;
	}

	void Label::setColor(const Vector4 &color)
	{
		_color = color;

		repaint();
	}

	const Vector4 &Label::getColor() const
	{
		return _color;
	}

	void Label::setPosition(const Vector3 &position)
	{
		_position = position;
		repaint();
	}

	const Vector3 &Label::getPosition() const
	{
		return _position;
	}

	const Sprite *Label::getData() const
	{
		return _characters.data();
	}

	const size_t Label::getCount() const
	{
		return _characters.size();
	}

	void Label::repaint()
	{
		_characters.clear();
		_textures.clear();

		const Glyph &g = _font.getGlyph();

		float x = _position.x;
		float y = _position.y;

		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
		std::wstring result = convert.from_bytes(_text);

		for (std::wstring::const_iterator i = result.begin(); i != result.end(); i++)
		{
			_font.loadCharacter(*i);

			float x2 = x + g->bitmap_left;
			float y2 = y - (g->bitmap.rows - g->bitmap_top);

			Texture *tex;
			auto a = _textures.find(*i);
			if (a != _textures.end())
			{
				tex = _textures[*i].get();
			}
			else
			{
				tex = new Texture(Metric2(g->bitmap.width, g->bitmap.rows), g->bitmap.buffer, GL_ALPHA);
				_textures[*i] = std::shared_ptr<Texture>(tex);
			}

			Sprite glyph = Sprite(Vector3(x2, y2, _position.z), Metric2(g->bitmap.width, g->bitmap.rows), Vector4(1, 1, 1, 1), tex, SpriteState::GLYPH);
			glyph.uvs[0] = Vector2(0, 1);
			glyph.uvs[1] = Vector2(1, 1);
			glyph.uvs[2] = Vector2(1, 0);
			glyph.uvs[3] = Vector2(0, 0);

			glyph.color = _color;

			x += (g->advance.x >> 6);
			y -= (g->advance.y >> 6);

			_characters.push_back(glyph);
		}
	}

}