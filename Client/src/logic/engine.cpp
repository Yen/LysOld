#include "engine.hpp"

#include <GL\glew.h>
#include <sstream>
#include <thread>
#include <future>
#include <atomic>

#include "..\lys.hpp"
#include "..\utils.hpp"
#include "..\maths.hpp"
#include "level.hpp"
#include "..\levels\menu.hpp"

namespace lys
{

	Engine::Engine()
		: _window("Lys", Metric2(960, 540), false),

		_mainContext(_window),
		_loadingContext(_window),

		_loadingScreen([&]() -> LoadingScreen
	{
		_loadingContext.makeCurrent();
		return LoadingScreen(_internals, EngineLoadingArgs{ _loadingContext });
	}()),

		_loading(false),
		_swapInterval(0),
		_internals{ *this, _window, _profile, _counter, _typeEngine }
	{
		_timer.reset();

		_mainContext.makeCurrent();
		_mainContext.setSwapInterval(_swapInterval);
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

		_loadingContext.makeCurrent();
		_loadingContext.setSwapInterval(_swapInterval);
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

		_loadingScreen.resize(_internals);
	}

	Engine::~Engine()
	{
		LYS_LOG("Waiting for other engine threads to clean up");

		if (_loadingThread != nullptr)
			_loadingThread->join();
	}

	void Engine::run()
	{
		if (!_loading && _level == nullptr)
			throw std::exception("No level was set for engine to start");

		_timer.reset();
		const FixedTimerData &time = _timer.getTimerData();

		WindowMessage message;
		unsigned int seconds = 0;
		unsigned int frames = 0;

		LYS_LOG("Engine loop (%p) started", this);

		_timer.reset();

		_window.setVisible(true);
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
				if (_loadingException != nullptr)
				{
					LYS_LOG("Exception was thrown in engine loading thread");
					std::rethrow_exception(_loadingException);
				}
				level = _level.get();
				context = &_mainContext;

				context->makeCurrent();
				if (_levelNew)
				{
					resize(*level);
					_levelNew = false;
				}
			}

			EngineArgs args{ time, *context };

			if (context->getSwapInterval() != _swapInterval)
				context->setSwapInterval(_swapInterval);

			while (_window.pollMessages(message))
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
					break;
				}
				case WindowMessage::KEYDOWN:
				{
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
				while ((time.current - _levelStart) * _level->getUPS() > _levelUpdates)
				{
					level->update(_internals, args);
					_levelUpdates++;
				}
			}

			if (_loading && (level != &_loadingScreen))
				continue;

			// Draw

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			level->draw(_internals, args);

			_window.swapBuffers();
			_counter.push(time.current);

			// End

			if (time.current > seconds)
			{
				std::stringstream title;
				title << "Lys FPS: " << _counter.getFPS(time.current).fps;
				_window.setTitle(title.str());

				seconds++;
			}
		}

		LYS_LOG("Engine loop (%p) escaped", this);

		_window.setVisible(false);

		glFinish();
	}

	void Engine::resize(Level &level)
	{
		glViewport(0, 0, _window.getSize().x, _window.getSize().y);
		level.resize(_internals);
	}

}