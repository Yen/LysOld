#pragma once

#include "..\uielement.hpp"
#include "..\..\maths.hpp"

namespace lys
{

	class TestElement : public UIElement
	{
	private:
		Vector3 _position;
		Vector2 _size;
	public:
		TestElement(const Vector3 &position, const Vector2 &size);

		void draw(Window *window, const FixedTimerData &time) override;
	};

}