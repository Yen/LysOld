#pragma once

#include <vector>
#include <memory>
#include <string>
#include <map>

#include "..\multisprite.hpp"
#include "..\texture.hpp"
#include "..\font.hpp"

namespace lys
{

	class Label : public MultiSprite
	{
	private:
		Vector3 _position;
		std::vector<Sprite> _characters;
		std::map<wchar_t, std::shared_ptr<Texture>> _textures;
		Font _font;
		std::string _text;
		Vector4 _color;
	public:
		Label(const std::string &text, const Vector3 &position);
		Label(const std::string &text, const Vector3 &position, const Font &font);
		Label(const std::string &text, const Vector3 &position, const Vector4 &color, const Font &font);

		void setText(const std::string &text);
		const std::string &getText() const;

		void setFont(const Font &font);
		Font &getFont();

		void setColor(const Vector4 &color);
		const Vector4 &getColor() const;

		const Sprite *getData() const override;
		const size_t getCount() const override;
	private:
		void repaint();
	};

}