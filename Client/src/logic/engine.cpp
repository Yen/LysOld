#include "engine.hpp"

#include <GL\glew.h>
#include <sstream>

#include "..\lys.hpp"
#include "..\maths.hpp"
#include "..\utils.hpp"

namespace lys
{

	Engine::Engine()
	{
		_window = new Window("Lys", Metric2(960, 540), false);
		_timer = new FixedTimer;
		_spriteBatch = new SpriteBatch;
		_meshBatch = new MeshBatch;
	}

	Engine::~Engine()
	{
		delete _meshBatch;
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

		MeshData test2 = utils::loadMeshOBJ("");

		//

		_spriteBatch->resize(_window->getSize());
		_meshBatch->resize(_window->getSize());

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
					_meshBatch->resize(_window->getSize());
					break;
				}
				}

				if (!running) break;
			}
			if (!running) continue;

			_timer->update();

			// Draw

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Meshbatch

			_meshBatch->submit(&test2);

			_meshBatch->renderBatch();

			// Spritebatch

			_spriteBatch->submit(&test);

			_spriteBatch->renderBatch();

			//

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