#include "engine.hpp"

#include <GL\glew.h>
#include <sstream>
#include <thread>
#include <future>
#include <atomic>

#include "..\lys.hpp"
#include "..\maths.hpp"
#include "level.hpp"
#include "..\levels\menu.hpp"
#include "..\levels\loadingscreen.hpp"

namespace lys
{

	static LoadingScreen createLoadingScreen(GraphicsContext &context)
	{
		context.makeCurrent();
		return LoadingScreen();
	}

	static DebugOverlay createDebugOverlay(GraphicsContext &context)
	{
		context.makeCurrent();
		return DebugOverlay();
	}

	Engine::Engine()
		: _core{ Window("Lys", Metric2(960, 540), false), FPSCounter() },
		_mainContext(_core.window),
		_loadingContext(_core.window),
		_debugContext(_core.window),
		_loadingScreen(createLoadingScreen(_loadingContext)),
		_debugOverlay(createDebugOverlay(_debugContext)),
		_loading(false),
		_swapInterval(0)
	{
		_timer.reset();

		_mainContext.makeCurrent();
		_mainContext.setSwapInterval(_swapInterval);
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

		_debugContext.makeCurrent();
		_debugContext.setSwapInterval(_swapInterval);
		//Should never be cleared from this context
		glClearColor(1.0f, 0.5f, 0.5f, 1.0f);

		_loadingContext.makeCurrent();
		_loadingContext.setSwapInterval(_swapInterval);
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

		_loadingScreen.resize(_core);

		changeLevel<Menu>(_timer.getTimerData());
	}

	Engine::~Engine()
	{

	}

	void Engine::run()
	{
		_timer.reset();
		const FixedTimerData &time = _timer.getTimerData();

		WindowMessage message;
		unsigned int seconds = 0;
		unsigned int frames = 0;

		LYS_LOG("Engine loop (%p) started", this);

		_timer.reset();

		_core.window.setVisible(true);
		bool running = true;
		while (running)
		{
			Level *level;
			GraphicsContext *context;

			if (_loading)
			{
				level = &_loadingScreen;
				context = &_loadingContext;
				context->makeCurrent();
			}
			else
			{
				level = _level.get();
				context = &_mainContext;
				context->makeCurrent();
				if (_levelNew)
				{
					resize(*level);
					_levelNew = false;
				}
			}

			if (context->getSwapInterval() != _swapInterval)
				context->setSwapInterval(_swapInterval);

			while (_core.window.pollMessages(message))
			{
				switch (message)
				{
				case WindowMessage::CLOSE:
				{
					running = false;
					break;
				}
				case WindowMessage::FOCUSGAINED:
				{
					_swapInterval = 0;
					break;
				}
				case WindowMessage::FOCUSLOST:
				{
					_swapInterval = 1;
					break;
				}
				case WindowMessage::WINDOWSIZECHANGED:
				{
					resize(*level);
					_debugContext.makeCurrent();
					resize(_debugOverlay);
					context->makeCurrent();
					break;
				}
				case WindowMessage::KEYDOWN:
				{
					if (_core.window.getKey(SDL_SCANCODE_F11))
						_debug = !_debug;
					break;
				}
				}

				if (!running) break;
			}
			if (!running) continue;

			_timer.update();

			// Update

			if (level->getUPS() != 0)
			{
				TimePoint a = time.current - _levelStart;
				while ((time.current - _levelStart) * _level->getUPS() > _levelUpdates)
				{
					level->update(_core, time);
					_levelUpdates++;
				}
			}

			// Draw

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			level->draw(_core, time);

			if (_debug)
			{
				_debugContext.makeCurrent();
				_debugOverlay.draw(_core, time);
			}

			_core.window.swapBuffers();
			_core.counter.push(time.current);

			// End

			if (time.current > seconds)
			{
				std::stringstream title;
				title << "Lys FPS: " << _core.counter.getFPS(time.current);
				_core.window.setTitle(title.str());

				seconds++;
			}
		}

		LYS_LOG("Engine loop (%p) escaped", this);

		_core.window.setVisible(false);

		LYS_LOG("Waiting for other threads to cleanup");

		_loadingThread->join();
	}

	template <typename T>
	void Engine::changeLevel(const FixedTimerData &time)
	{
		static_assert(std::is_base_of<Level, T>::value, "Not base class of Level");

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
			_level = std::make_unique<T>(*(new T));
			_levelStart = time.current;
			_levelUpdates = 0;
			_levelNew = true;

			_mainContext.unbindCurrent();
			_loading = false;
		});
	}

	void Engine::resize(Level &level)
	{
		glViewport(0, 0, _core.window.getSize().x, _core.window.getSize().y);
		level.resize(_core);
	}

}