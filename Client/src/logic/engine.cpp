#include "engine.hpp"

#include <GL\glew.h>
#include <sstream>

#include "..\lys.hpp"
#include "..\maths.hpp"
#include "..\utils.hpp"
#include "..\graphics\interfacebatch.hpp"

namespace lys
{

	Engine::Engine()
		: _window(Window("Lys", Metric2(960, 540), false))
	{

	}

	Engine::~Engine()
	{

	}

	void Engine::run()
	{
		_timer.reset();
		const FixedTimerData &time = _timer.getTimerData();

		WindowMessage message;
		int seconds = 0;
		int frames = 0;

		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

		InterfaceBatch batch;

		Texture tex("data/images/spectrum.jpg");

		Sprite test(Vector3(10, 10, 0), Vector2(200, 200), Vector4(1, 1, 1, 1), &tex);
		Sprite test2(Vector3(210, 210, 0), Vector2(100, 100), Vector4(1, 0, 1, 1));

		//

		batch.resize(_window.getSize());

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
					batch.resize(_window.getSize());
					break;
				}
				}

				if (!running) break;
			}
			if (!running) continue;

			_timer.update();

			// Draw

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			batch.submit(&test);
			batch.submit(&test2);
			batch.renderBatch();

			_window.swapBuffers();
			frames++;

			// End draw

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