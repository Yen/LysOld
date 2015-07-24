#include "engine.hpp"

#include <GL\glew.h>
#include <sstream>

#include "..\lys.hpp"
#include "..\maths.hpp"
#include "levels\menu.hpp"

namespace lys
{

	Engine::Engine()
		: _window(Window("Lys", Metric2(960, 540), false)), _level(std::unique_ptr<Level>(new Menu))
	{

	}

	Engine::~Engine()
	{

	}

	void Engine::run()
	{
		_timer.reset();
		const FixedTimerData &time = _timer.getTimerData();

		TimePoint levelStart = time.current;
		unsigned int updates = 0;

		WindowMessage message;
		unsigned int seconds = 0;
		unsigned int frames = 0;

		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

		_level->resize(_window);

		//

		LYS_LOG("Engine loop started");

		_timer.reset();
		_window.setVisible(true);
		bool running = true;
		while (running)
		{
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
					_window.setSwapInterval(0);
					break;
				}
				case WindowMessage::FOCUSLOST:
				{
					_window.setSwapInterval(1);
					break;
				}
				case WindowMessage::WINDOWSIZECHANGED:
				{
					glViewport(0, 0, _window.getSize().x, _window.getSize().y);
					_level->resize(_window);
					break;
				}
				}

				if (!running) break;
			}
			if (!running) continue;

			_timer.update();

			// Update

			while ((time.current - levelStart) * _level->getUPS() > updates)
			{
				_level->update(_window, time);
				updates++;
			}

			// Draw

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			_level->draw(_window, time);

			_window.swapBuffers();
			frames++;

			// End

			if (time.current > seconds)
			{
				std::stringstream title;
				title << "Lys FPS: " << frames;
				_window.setTitle(title.str());

				seconds++;
				frames = 0;
			}
		}
	}

}