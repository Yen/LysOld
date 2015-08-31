#pragma once

#include <memory>
#include <thread>
#include <atomic>

#include "..\graphics\window.hpp"
#include "..\graphics\graphicscontext.hpp"
#include "fixedtimer.hpp"
#include "fpscounter.hpp"
#include "..\levels\loadingscreen.hpp"
#include "..\levels\debugoverlay.hpp"

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
		GraphicsContext _mainContext;
		GraphicsContext _loadingContext;
		GraphicsContext _debugContext;
		LoadingScreen _loadingScreen;
		DebugOverlay _debugOverlay;
		std::atomic<bool> _loading;
		std::unique_ptr<std::thread> _loadingThread;
		TimePoint _levelStart;
		unsigned int _levelUpdates;
		std::atomic<bool> _levelNew;
		int _swapInterval;
		bool _debug;
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