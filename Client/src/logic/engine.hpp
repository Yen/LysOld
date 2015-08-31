#pragma once

#include <memory>
#include <thread>
#include <atomic>

#include "..\graphics\window.hpp"
#include "..\graphics\graphicscontext.hpp"
#include "fixedtimer.hpp"
#include "fpscounter.hpp"
#include "..\levels\loadingscreen.hpp"

namespace lys
{

	class EngineCore
	{
	public:
		Window window;
		FPSCounter counter;
		GraphicsContext context;
		GraphicsContext loading;
	};

	class Level;

	class Engine
	{
	private:
		EngineCore _core;
		FixedTimer _timer;
		std::unique_ptr<Level> _level;
		LoadingScreen _loadingScreen;
		std::atomic<bool> _loading;
		std::unique_ptr<std::thread> _loadingThread;
		TimePoint _levelStart;
		unsigned int _levelUpdates;
		std::atomic<bool> _levelNew;
		int _swapInterval;
	public:
		Engine();
		~Engine();

		void run();
	private:
		template <typename T>
		void changeLevel(const FixedTimerData &time);
		void resize(Level &level);
	};

}