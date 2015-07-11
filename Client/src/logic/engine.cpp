#include "engine.hpp"

#include <GL\glew.h>
#include <sstream>

#include "..\lys.hpp"
#include "..\maths.hpp"
#include "fixedtimer.hpp"
#include "..\graphics\shaderprogram.hpp"
#include "..\utils.hpp"

namespace lys
{

	const int fps = 60;

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
		glDisable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

		std::vector<ShaderData> shaders;
		shaders.push_back(ShaderData(GL_VERTEX_SHADER, utils::readFile("data/basic.vert")));
		shaders.push_back(ShaderData(GL_FRAGMENT_SHADER, utils::readFile("data/basic.frag")));

		ShaderProgram shader(shaders);
		shader.enable();

		Matrix4 pr = Matrix4::perspectivefov(M_PI / 4.0f, _window->getSize().x / _window->getSize().y, 1, 100);
		Matrix4 vw = Matrix4::lookAt(Vector3(0.0f, 3.0f, -5.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));

		shader.setUniformMat4("uni_pr_matrix", pr);
		shader.setUniformMat4("uni_vw_matrix", vw);

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

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glBegin(GL_QUADS);
			glVertex3f(-0.5f, -0.5f, 0.0f);
			glVertex3f( 0.5f, -0.5f, 0.0f);
			glVertex3f( 0.5f,  0.5f, 0.0f);
			glVertex3f(-0.5f,  0.5f, 0.0f);
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