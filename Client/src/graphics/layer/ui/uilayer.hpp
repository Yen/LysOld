#pragma once

#include "..\layer.hpp"
#include "uielement.hpp"

namespace lys
{

	class UILayer : public Layer<UIElement>
	{
	public:
		void push(UIElement &data) override;

		void flush() override;
	};

}