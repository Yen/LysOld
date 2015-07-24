#pragma once

#include "..\window.hpp"
#include "fixedtimer.hpp"

namespace lys
{

	class Engine
	{
	private:
		Window _window;
		FixedTimer _timer;
	public:
		Engine();
		~Engine();

		void run();
	};

}