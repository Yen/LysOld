#pragma once

#include <vector>
#include <memory>
#include <string>
#include <map>

#include "..\multisprite.hpp"
#include "..\texture.hpp"
#include "..\font.hpp"
#include "..\type\typeface.hpp"

namespace lys
{

	class Label : public MultiSprite
	{
	private:
		Vector3 _position;
		std::vector<Sprite> _characters;
		std::map<wchar_t, std::shared_ptr<Texture>> _textures;
		TypeFace &_font;
		std::string _text;
		Vector4 _color;
	public:
		Label(const Vector3 &position);
		Label(const std::string &text, const Vector3 &position);
		Label(const std::string &text, const Vector3 &position, TypeFace &font);
		Label(const std::string &text, const Vector3 &position, const Vector4 &color, TypeFace &font);

		void setText(const std::string &text);
		const std::string &getText() const;

		void setFont(TypeFace &font);
		TypeFace &getFont() const;

		void setColor(const Vector4 &color);
		const Vector4 &getColor() const;

		void setPosition(const Vector3 &position);
		const Vector3 &getPosition() const;

		const Sprite *getData() const override;
		const size_t getCount() const override;

		void repaint();
	};

}