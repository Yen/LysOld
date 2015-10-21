#include "uilabel.hpp"

#include <locale>
#include <codecvt>
#include <algorithm>

#include "..\uilayer.hpp"

namespace lys
{

	UILabel::UILabel(const Vector2 &size, const Alignment &alignment, const Vector2 &offset, EngineInternals &internals, const bool &fixed, const std::string &text)
		: UIElementManaged(size, alignment, offset, nullptr, false), _typeEngine(internals.typeEngine), _fixed(fixed), _text(text)
	{}

	void UILabel::setText(const std::string &text)
	{
		_text = text;
	}

	const std::string &UILabel::getText() const
	{
		return _text;
	}

	void UILabel::setFixed(const bool &fixed)
	{
		_fixed = fixed;
	}

	const bool &UILabel::getFixed() const
	{
		return _fixed;
	}

	void UILabel::repaint(EngineInternals &internals, const UILayer &ui)
	{
		_elements.clear();
		_elementPointers.clear();
		_textures.clear();

		float x = 0;
		float y = 0;

		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
		std::wstring result = convert.from_bytes(_text);

		Vector2 resolution(size.x * ui.getRatio(), size.y * ui.getRatio());
		for (std::wstring::const_iterator i = result.begin(); i != result.end(); i++)
		{
			auto &g = _typeEngine.getGlyph(*i, (unsigned int)resolution.y);

			float x2 = x + (float)g.bitmap.left;
			float y2 = y + (resolution.y - (float)g.bitmap.top);

			Texture2D *tex;
			if (_textures.find(*i) != _textures.end())
			{
				tex = _textures[*i].get();
			}
			else
			{
				_textures[*i] = std::make_shared<Texture2D>(g.bitmap.buffer, Pixmap::Information(Metric2(g.bitmap.width, g.bitmap.height), Pixmap::Information::Format::ALPHA, 8));
				tex = _textures[*i].get();
			}

			UIElement glyph = UIElement(Vector2((float)g.bitmap.width / ui.getRatio(), (float)g.bitmap.height / ui.getRatio()), Alignment::TOP_LEFT, Vector2(x2 / ui.getRatio(), y2 / ui.getRatio()), tex);
			glyph.uvs[0] = Vector2(0, 0);
			glyph.uvs[1] = Vector2(1, 0);
			glyph.uvs[2] = Vector2(1, 1);
			glyph.uvs[3] = Vector2(0, 1);

			x += g.advance.x;
			y += g.advance.y;

			_elements.push_back(glyph);
		}
		for (auto &element : _elements)
		{
			_elementPointers.push_back(&element);
		}

		if (!_fixed)
		{
			size.x = x / ui.getRatio();
		}
	}

	const UIElement *const *UILabel::getChildren() const
	{
		return _elementPointers.data();
	}

	size_t UILabel::getChildrenCount() const
	{
		return _elements.size();
	}

}