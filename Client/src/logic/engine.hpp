#pragma once

#include <memory>

#include "..\window.hpp"
#include "fixedtimer.hpp"
#include "level.hpp"
#include "levels\menu.hpp"

namespace lys
{

	class Engine
	{
	private:
		Window _window;
		FixedTimer _timer;
		std::unique_ptr<Level> _level;
		TimePoint _levelStart;
		unsigned int _levelUpdates;
	public:
		Engine();
		~Engine();

		void run();
	private:
		template <typename T>
		void changeLevel(T *level, const FixedTimerData &time);
	};

}