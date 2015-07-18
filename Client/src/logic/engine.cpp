#include "engine.hpp"

#include <GL\glew.h>
#include <sstream>

#include "..\lys.hpp"
#include "..\maths.hpp"
#include "..\utils.hpp"
#include "..\graphics\texture.hpp"
#include "..\graphics\framebuffer.hpp"
#include "..\graphics\spritebatch.hpp"

namespace lys
{

	Engine::Engine()
	{
		LYS_LOG("Creating new engine");
		_window = new Window("Lys", Metric2(960, 540), false);
		_timer = new FixedTimer;
	}

	Engine::~Engine()
	{
		LYS_LOG("Destroying engine");
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

		//

		SpriteBatch batch;
		batch.resize(_window->getSize());

		SpriteData test;
		test.position = Vector3(0, 0, 0);
		test.size = Vector2(100, 100);
		test.color = Vector4(1, 1, 1, 1);
		test.texture = nullptr;

		Texture tex("data/images/dank.png");

		SpriteData test2;
		test2.position = Vector3(100, 100, 1);
		test2.size = Vector2(100, 100);
		test2.color = Vector4(1, 1, 1, 2);
		test2.texture = &tex;

		SpriteData test3;
		test3.position = Vector3(200, 200, 2);
		test3.size = Vector2(200, 200);
		test3.color = Vector4(1, 1, 1, 1);
		test3.texture = nullptr;

		//

		_timer->reset();
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
					batch.resize(_window->getSize());
					break;
				}
				}

				if (!running) break;
			}
			if (!running) continue;

			_timer->update();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			batch.submit(&test);
			batch.submit(&test2);
			batch.submit(&test3);

			batch.renderBatch();

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