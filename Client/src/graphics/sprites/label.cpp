#include "label.hpp"

#include <locale>
#include <codecvt>
#include <algorithm>

#include "..\..\lys.hpp"

namespace lys
{

#define LYS_LABEL_DEFAULT_HEIGHT 20

	Label::Label(TypeFace &face)
		: Label(face, Vector3(0, 0, 0))
	{}

	Label::Label(TypeFace &face, const Vector3 &position)
		: Label(face, Vector3(0, 0, 0), std::string())
	{}

	Label::Label(TypeFace &face, const Vector3 &position, const std::string &text)
		: Label(face, position, text, LYS_LABEL_DEFAULT_HEIGHT)
	{}

	Label::Label(TypeFace &face, const Vector3 &position, const std::string &text, const unsigned int &height)
		: Label(face, position, text, height, Vector4(1, 1, 1, 1))
	{}

	Label::Label(TypeFace &face, const Vector3 &position, const std::string &text, const unsigned int &height, const Vector4 &color)
		: _face(&face), _position(position), _text(text), _height(height), _color(color)
	{}

	void Label::setText(const std::string &text)
	{
		_text = text;
	}

	const std::string &Label::getText() const
	{
		return _text;
	}

	void Label::setHeight(const unsigned int height)
	{
		_height = height;
	}

	const unsigned int &Label::getHeight() const
	{
		return _height;
	}

	void Label::setFace(TypeFace &face)
	{
		_face = &face;
	}

	const TypeFace &Label::getFace() const
	{
		return *_face;
	}

	void Label::setColor(const Vector4 &color)
	{
		_color = color;
	}

	const Vector4 &Label::getColor() const
	{
		return _color;
	}

	void Label::setPosition(const Vector3 &position)
	{
		_position = position;
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

	void Label::repaint(EngineInternals &internals)
	{
		_characters.clear();
		_textures.clear();

		float x = _position.x;
		float y = _position.y;

		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
		std::wstring result = convert.from_bytes(_text);

		for (std::wstring::const_iterator i = result.begin(); i != result.end(); i++)
		{
			Glyph &g = internals.typeEngine.getGlyph(*i, _height, *_face);

			float x2 = x + g.bitmap.left;
			float y2 = y - ((float)g.bitmap.height - (float)g.bitmap.top);

			Texture *tex;
			if (_textures.find(*i) != _textures.end())
			{
				tex = _textures[*i].get();
			}
			else
			{
				_textures[*i] = std::make_shared<Texture>(Metric2(g.bitmap.width, g.bitmap.height), g.bitmap.buffer, GL_ALPHA);
				tex = _textures[*i].get();
			}

			Sprite glyph = Sprite(Vector3(x2, y2, _position.z), Metric2(g.bitmap.width, g.bitmap.height), Vector4(1, 1, 1, 1), tex, SpriteState::GLYPH);
			glyph.uvs[0] = Vector2(0, 1);
			glyph.uvs[1] = Vector2(1, 1);
			glyph.uvs[2] = Vector2(1, 0);
			glyph.uvs[3] = Vector2(0, 0);

			glyph.color = _color;

			x += g.advance.x;
			y -= g.advance.y;

			_characters.push_back(glyph);
		}
	}

}