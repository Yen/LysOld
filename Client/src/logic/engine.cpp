#include "engine.hpp"

#include <GL\glew.h>
#include <sstream>

#include "..\lys.hpp"
#include "..\maths.hpp"
#include "..\utils.hpp"
#include "..\graphics\texture.hpp"

namespace lys
{

	Engine::Engine()
	{
		_window = new Window("Lys", Metric2(960, 540), false);
		_timer = new FixedTimer;
		_spriteBatch = new SpriteBatch;
	}

	Engine::~Engine()
	{
		delete _spriteBatch;
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

		SpriteData tests[600];
		for (int i = 0; i < 600; i++)
		{
			tests[i] = { Vector3((float)i * 4, 0, 3), Vector2(4,4), Vector4(1,1,1,1), nullptr };
		}

		//

		_spriteBatch->resize(_window->getSize());

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
					_spriteBatch->resize(_window->getSize());
					break;
				}
				}

				if (!running) break;
			}
			if (!running) continue;

			_timer->update();

			// Draw

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			_spriteBatch->submit(&test);
			_spriteBatch->submit(&test2);
			_spriteBatch->submit(&test3);

			for (int i = 0; i < 600; i++)
			{
				_spriteBatch->submit(&tests[i]);
			}

			_spriteBatch->renderBatch();

			_window->swapBuffers();
			frames++;

			// End draw

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