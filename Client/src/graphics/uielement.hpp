#pragma once

#include "..\maths.hpp"
#include "texture.hpp"

namespace lys
{

	class UIElement
	{
	public:
		Vector3 position;
		Vector2 size;
		Vector4 color;
		const Texture *texture;
	};

}