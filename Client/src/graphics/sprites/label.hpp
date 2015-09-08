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
		TypeFace *_face;
	public:
		Label(TypeFace &face);
		Label(TypeFace &face, const Vector3 &position);
		Label(TypeFace &face, const Vector3 &position, const std::string &text);
		Label(TypeFace &face, const Vector3 &position, const std::string &text, const unsigned int &height);
		Label(TypeFace &face, const Vector3 &position, const std::string &text, const unsigned int &height, const Vector4 &color);

		void setText(const std::string &text);
		const std::string &getText() const;

		void setHeight(const unsigned int height);
		const unsigned int &getHeight() const;

		void setFace(TypeFace &face);
		const TypeFace &getFace() const;

		void setColor(const Vector4 &color);
		const Vector4 &getColor() const;

		void setPosition(const Vector3 &position);
		const Vector3 &getPosition() const;

		const Sprite *getData() const override;
		const size_t getCount() const override;

		void repaint(EngineInternals &internals);
	};

}