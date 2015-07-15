#pragma once

#include "..\uielement.hpp"

namespace lys
{

	class TestElement : public UIElement
	{
	public:
		TestElement(const Vector3 &position, const Vector2 &size, const Vector4 &color, Texture *texture);
	};

}