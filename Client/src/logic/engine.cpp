#include "engine.hpp"

#include <GL\glew.h>
#include <sstream>

#include "..\lys.hpp"
#include "..\maths.hpp"
#include "level.hpp"
#include "levels\menu.hpp"

namespace lys
{

	Engine::Engine()
		: _core{ Window("Lys", Metric2(960, 540), false), FPSCounter() }
	{
		_timer.reset();
		changeLevel(new Menu, _timer.getTimerData());
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

		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

		_level->resize(_core);

		//

		LYS_LOG("Engine loop (%p) started", this);

		_timer.reset();
		_core.window.setVisible(true);
		bool running = true;
		while (running)
		{
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
					_core.window.setSwapInterval(0);
					break;
				}
				case WindowMessage::FOCUSLOST:
				{
					_core.window.setSwapInterval(1);
					break;
				}
				case WindowMessage::WINDOWSIZECHANGED:
				{
					glViewport(0, 0, _core.window.getSize().x, _core.window.getSize().y);
					_level->resize(_core);
					break;
				}
				}

				if (!running) break;
			}
			if (!running) continue;

			_timer.update();

			// Update

			if (_level->getUPS() != 0)
			{
				while ((time.current - _levelStart) * _level->getUPS() > _levelUpdates)
				{
					_level->update(_core, time);
					_levelUpdates++;
				}
			}

			// Draw

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			_level->draw(_core, time);

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
	}

	template <typename T>
	void Engine::changeLevel(T *level, const FixedTimerData &time)
	{
		static_assert(std::is_base_of<Level, T>::value, "Not base class of Level");
		_level = std::make_unique<T>(*level);
		_levelStart = time.current;
		_levelUpdates = 0;
	}

}