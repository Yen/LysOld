#include "sprite.hpp"

namespace lys
{

	Sprite::Sprite()
		: Sprite(Vector3(0, 0, 0), Vector2(0, 0))
	{}

	Sprite::Sprite(const Vector3 &position, const Vector2 &size)
		: Sprite(position, size, nullptr)
	{}

	Sprite::Sprite(const Vector3 &position, const Vector2 &size, const Vector4 &color)
		: Sprite(position, size, color, nullptr)
	{}

	Sprite::Sprite(const Vector3 &position, const Vector2 &size, const Texture2D *texture)
		: Sprite(position, size, Vector4(1, 1, 1, 1), texture)
	{}

	Sprite::Sprite(const Vector3 &position, const Vector2 &size, const Vector4 &color, const Texture2D *texture)
		: Sprite(position, size, color, texture, SpriteState::DEFAULT)
	{}

	Sprite::Sprite(const Vector3 &position, const Vector2 &size, const Vector4 &color, const Texture2D *texture, const SpriteState &state)
		: position(position), size(size), color(color), texture(texture), uvs({ Vector2(0, 0), Vector2(1, 0), Vector2(1, 1), Vector2(0, 1) }), state(state)
	{}

}