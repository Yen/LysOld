#pragma once

#include <memory>
#include <thread>
#include <atomic>
#include <future>

#include "..\graphics\window.hpp"
#include "..\graphics\graphicscontext.hpp"
#include "..\graphics\graphicsprofile.hpp"
#include "..\graphics\shaderprogram.hpp"
#include "fixedtimer.hpp"
#include "fpscounter.hpp"
#include "..\graphics\typeengine.hpp"
#include "..\levels\loadingscreen.hpp"

namespace lys
{

	class EngineLoadingArgs
	{
	public:
		const GraphicsContext &context;
	};

	class Engine;

	class EngineInternals
	{
	public:
		Engine &engine;
		Window &window;
		const GraphicsProfile &profile;
		FPSCounter &counter;
		TypeEngine &typeEngine;
		LoadingScreen &loadingScreen;
	};

	class EngineArgs
	{
	public:
		const FixedTimerData &time;
		GraphicsContext &context;
	};

	class Level;

	class Engine
	{
	private:
		Window _window;
		FPSCounter _counter;
		TypeEngine _typeEngine;
		FixedTimer _timer;

		GraphicsContext _mainContext;
		GraphicsContext _loadingContext;

		GraphicsProfile _profile;

		std::unique_ptr<Level> _level;

		std::atomic<bool> _loading;
		std::unique_ptr<std::thread> _loadingThread;
		std::exception_ptr _loadingException;

		TimePoint _levelStart;
		unsigned int _levelUpdates;
		std::atomic<bool> _levelNew;

		int _swapInterval;
		EngineInternals _internals;

		LoadingScreen _loadingScreen;
	public:
		Engine();
		~Engine();

		void run();
	private:
		void resize(Level &level);
	public:
		template <typename T, typename ...A>
		void changeLevel(A &&...args)
		{
			static_assert(std::is_base_of<Level, T>::value, "Not base class of Level");
			static_assert(std::is_constructible<T, EngineInternals &, const EngineLoadingArgs &, A...>::value, "Level must contain correct constructor");

			if (_loading)
			{
				LYS_LOG_WARNING("Change level(%s) aborted, a level is already loading", typeid(T).name());
				return;
			}

			LYS_LOG("Changing level (%s)", typeid(T).name());

			glFinish();

			_loading = true;

			_loadingContext.makeCurrent();

			if (_loadingThread != nullptr)
			{
				_loadingThread->join();
				_loadingThread.release();
			}
			_loadingThread = std::make_unique<std::thread>([&]()
			{
				_mainContext.makeCurrent();

				try
				{
					_level = std::make_unique<T>(_internals, EngineLoadingArgs{ _mainContext }, args...);
					_loadingScreen.setLoadingText();
					_levelStart = _timer.getTimerData().current;
					_levelUpdates = 0;
					_levelNew = true;
				}
				catch (...)
				{
					_loadingException = std::current_exception();
				}

				_mainContext.unbindCurrent();
				_loading = false;
			});

			resize(_loadingScreen);
		}
	};

}