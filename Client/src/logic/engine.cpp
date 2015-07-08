#include "engine.hpp"

#include <GL\glew.h>
#include <sstream>

#include "..\lys.hpp"
#include "..\maths.hpp"
#include "fixedtimer.hpp"

namespace lys
{

	Engine::Engine()
	{
		LYS_LOG("Creating new engine");
		_window = new Window("Lys", Metric2(960, 540), false);
	}

	Engine::~Engine()
	{
		LYS_LOG("Destroying engine");
		delete _window;
	}

	void Engine::run()
	{
		FixedTimer timer;
		const FixedTimerData &time = timer.getTimerData();

		WindowMessage message;
		int seconds = 0;
		int frames = 0;

		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

		_window->setVisible(true);
		bool running = true;
		while (running)
		{
			while (_window->pollMessages(message))
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
					_window->setSwapInterval(0);
					break;
				}
				case WindowMessage::FOCUSLOST:
				{
					_window->setSwapInterval(1);
					break;
				}
				case WindowMessage::WINDOWSIZECHANGED:
				{
					glViewport(0, 0, _window->getSize().x, _window->getSize().y);
					break;
				}
				}

				if (!running) break;
			}
			if (!running) continue;

			timer.update();

			glClear(GL_COLOR_BUFFER_BIT);

			glBegin(GL_QUADS);
			glVertex2f(-0.5f, -0.5f);
			glVertex2f(0.5f, -0.5f);
			glVertex2f(0.5f, 0.5f);
			glVertex2f(-0.5f, 0.5f);
			glEnd();

			_window->swapBuffers();
			frames++;

			if (time.current > seconds)
			{
				std::stringstream title;
				title << "Lys FPS: " << frames;
				_window->setTitle(title.str());

				seconds++;
				frames = 0;
			}
		}
	}

}