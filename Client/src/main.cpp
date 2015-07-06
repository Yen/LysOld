#include "lys.hpp"

#include <SDL\SDL_main.h>
#include <GL\glew.h>
#include <sstream>

#include "window.hpp"
#include "logic\fixedtimer.hpp"

namespace lys
{

	int run()
	{
		try
		{
			FixedTimer timer;
			const FixedTimerData &time = timer.getTimerData();

			WindowMessage message;
			Window window("Lys", Metric2(960, 540), false);
			window.setVisible(true);

			glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

			timer.reset();

			int seconds = 0;
			int frames = 0;
			bool running = true;
			while (running)
			{
				while (window.pollMessages(message))
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
						window.setSwapInterval(0);
						break;
					}
					case WindowMessage::FOCUSLOST:
					{
						window.setSwapInterval(1);
						break;
					}
					}


					if (!running) break;
				}
				if (!running) continue;

				timer.update();

				glClear(GL_COLOR_BUFFER_BIT);
				window.swapBuffers();
				frames++;

				if (time.current > seconds)
				{
					std::stringstream title;
					title << "Lys" << " FPS: " << frames;
					window.setTitle(title.str());
					seconds++;
					frames = 0;
				}
			}
		}
		catch (const std::exception &e)
		{
			LYS_LOG_ERR("Unhandled standard exception occured (%s)", e.what());
			return 1;
		}
		catch (...)
		{
			LYS_LOG_ERR("Unhandled unknown exception type occured");
			return 1;
		}

		return 0;
	}

}

int main(int argc, char *argv[])
{
	LYS_LOG_APP("Lys");
	for (int i = 0; i < argc; i++)
	{
		LYS_LOG_APP("Launch arguments[%d]: \"%s\"", i, argv[i]);
	}

	// Version checker or something

	LYS_LOG_APP("Executing run function");
	int execution = lys::run();
	LYS_LOG_APP("Run function complete, return code: (%d)", execution);

	// Clean up code?

	LYS_LOG_APP("Program reached exit point safely");

	LYS_PAUSE;

	return 0;
}