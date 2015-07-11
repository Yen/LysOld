#pragma once

#include "..\window.hpp"
#include "fixedtimer.hpp"
#include "..\graphics\uimanager.hpp"

namespace lys
{

	class Engine
	{
	private:
		Window *_window;
		FixedTimer *_timer;
		UIManager *_uimanager;
	public:
		Engine();
		~Engine();

		void run();
	};

}