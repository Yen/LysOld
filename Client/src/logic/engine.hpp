#pragma once

#include "..\window.hpp"

namespace lys
{

	class Engine
	{
	private:
		Window *_window;
	public:
		Engine();
		~Engine();

		void run();
	};

}