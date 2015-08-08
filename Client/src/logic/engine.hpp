#pragma once

#include <memory>

#include "..\window.hpp"
#include "fixedtimer.hpp"
#include "fpscounter.hpp"

namespace lys
{

	class EngineCore
	{
	public:
		Window window;
		FPSCounter counter;
	};

	class Level;

	class Engine
	{
	private:
		EngineCore _core;
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