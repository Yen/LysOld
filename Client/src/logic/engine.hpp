#pragma once

#include <memory>

#include "..\window.hpp"
#include "fixedtimer.hpp"
#include "level.hpp"
#include "levels\menu.hpp"
#include "fpscounter.hpp"

namespace lys
{

	class EngineCore
	{
	public:
		Window &window;
		FPSCounter &counter;
	};

	class Engine
	{
	private:
		EngineCore _core;
		Window _window;
		FixedTimer _timer;
		std::unique_ptr<Level> _level;
		TimePoint _levelStart;
		unsigned int _levelUpdates;
		FPSCounter _fps;
	public:
		Engine();
		~Engine();

		void run();
	private:
		template <typename T>
		void changeLevel(T *level, const FixedTimerData &time);
	};

}