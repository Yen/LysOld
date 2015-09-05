#pragma once

#include <vector>
#include <memory>
#include <string>
#include <map>

#include "..\multisprite.hpp"
#include "..\texture.hpp"
#include "..\..\logic\engine.hpp"

namespace lys
{

	class Label : public MultiSprite
	{
	private:
		Vector3 _position;
		std::vector<Sprite> _characters;
		std::map<wchar_t, std::shared_ptr<Texture>> _textures;
		std::string _text;
		Vector4 _color;
		unsigned int _height;
		std::string _font;
	public:
		Label(const Vector3 &position, const unsigned int &height);
		Label(const std::string &text, const Vector3 &position, const unsigned int &height);
		Label(const std::string &text, const Vector3 &position, const unsigned int &height, const Vector4 &color);
		Label(const std::string &text, const Vector3 &position, const unsigned int &height, const Vector4 &color, const std::string &font);

		void setText(const std::string &text);
		const std::string &getText() const;

		void setHeight(const unsigned int height);
		const unsigned int &getHeight() const;

		void setFont(const std::string &font);
		const std::string &getFont() const;

		void setColor(const Vector4 &color);
		const Vector4 &getColor() const;

		void setPosition(const Vector3 &position);
		const Vector3 &getPosition() const;

		const Sprite *getData() const override;
		const size_t getCount() const override;

		void repaint(EngineInternals &internals);
	};

}