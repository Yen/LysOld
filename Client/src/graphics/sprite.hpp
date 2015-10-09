#pragma once

#include <array>

#include "..\maths.hpp"
#include "texture2d.hpp"

namespace lys
{

	enum SpriteState
	{
		DEFAULT = 0,
		GLYPH = 1
	};

	class Sprite
	{
	public:
		Vector3 position;
		Vector2 size;
		Vector4 color;
		const Texture2D *texture;
		std::array<Vector2, 4> uvs;
		SpriteState state;
	public:
		Sprite();
		Sprite(const Vector3 &position, const Vector2 &size);
		Sprite(const Vector3 &position, const Vector2 &size, const Vector4 &color);
		Sprite(const Vector3 &position, const Vector2 &size, const Texture2D *texture);
		Sprite(const Vector3 &position, const Vector2 &size, const Vector4 &color, const Texture2D *texture);
		Sprite(const Vector3 &position, const Vector2 &size, const Vector4 &color, const Texture2D *texture, const SpriteState &state);
	};

}