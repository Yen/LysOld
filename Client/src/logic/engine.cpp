#include "engine.hpp"

#include <GL\glew.h>
#include <sstream>

#include "..\lys.hpp"
#include "..\maths.hpp"
#include "..\utils.hpp"
#include "..\graphics\uielements\testelement.hpp"

namespace lys
{

	Engine::Engine()
	{
		LYS_LOG("Creating new engine");
		_window = new Window("Lys", Metric2(960, 540), false);
		_timer = new FixedTimer;

		_uimanager = new UIManager;
	}

	Engine::~Engine()
	{
		LYS_LOG("Destroying engine");
		delete _uimanager;
		delete _timer;
		delete _window;
	}

	void Engine::run()
	{
		_timer->reset();
		const FixedTimerData &time = _timer->getTimerData();

		WindowMessage message;
		int seconds = 0;
		int frames = 0;

		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

		TestElement a(Vector3(10.0f, 10.0f, 0.0f), Vector2(100.0f, 50.0f));
		TestElement b(Vector3(200.0f, 400.0f, 0.0f), Vector2(500.0f, 100.0f));

		_uimanager->resize(_window->getSize());

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
					_uimanager->resize(_window->getSize());
					break;
				}
				}

				if (!running) break;
			}
			if (!running) continue;

			_timer->update();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			_uimanager->push(&a);
			_uimanager->push(&b);

			_uimanager->flush(_window, time);

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