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
#include "..\graphics\type\typeengine.hpp"

namespace lys
{

	class EngineLoadingArgs
	{
	public:
		const GraphicsContext &context;
	};

	class EngineInternals
	{
	public:
		Window &window;
		FPSCounter &counter;
		TypeEngine &typeEngine;
	};

	class EngineArgs
	{
	public:
		const FixedTimerData &time;
		GraphicsContext &context;
	};

	class Level;

#define LYS_ENGINE_DEFAULT_FONT "opensans"

	class Engine
	{
	private:
		Window _window;
		FPSCounter _counter;
		TypeEngine _typeEngine;
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
		EngineInternals _internals;
	public:
		Engine();

		void run();
	private:
		void resize(Level &level);
	public:
		template <typename T>
		void changeLevel()
		{
			static_assert(std::is_base_of<Level, T>::value, "Not base class of Level");
			static_assert(std::is_constructible<T, EngineInternals &, const EngineLoadingArgs &>::value, "Level must contain correct constructor");

			if (_loading)
			{
				LYS_LOG_WARNING("Change level(%s) aborted, a level is already loading", typeid(T).name());
				return;
			}

			_loading = true;

			_loadingContext.makeCurrent();

			_loadingThread = std::make_unique<std::thread>([&]()
			{
				_mainContext.makeCurrent();
				_level = std::make_unique<T>(_internals, EngineLoadingArgs{ _loadingContext });
				_levelStart = _timer.getTimerData().current;
				_levelUpdates = 0;
				_levelNew = true;

				_mainContext.unbindCurrent();
				_loading = false;
			});
		}
	};

}