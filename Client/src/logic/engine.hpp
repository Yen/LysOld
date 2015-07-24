#pragma once

#include <memory>

#include "..\window.hpp"
#include "fixedtimer.hpp"
#include "level.hpp"

namespace lys
{

	class Engine
	{
	private:
		Window _window;
		FixedTimer _timer;
		std::unique_ptr<Level> _level;
	public:
		Engine();
		~Engine();

		void run();
	};

}