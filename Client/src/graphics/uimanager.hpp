#pragma once

#include <queue>

#include "shaderprogram.hpp"
#include "uielement.hpp"

namespace lys
{

	class UIManager
	{
	private:
		ShaderProgram *_shader;
		std::queue<UIElement *> _elements;
	public:
		UIManager();
		~UIManager();

		void push(UIElement *element);
		void flush(Window *window, const FixedTimerData &time);

		void resize(const Metric2 &size);
	};

}