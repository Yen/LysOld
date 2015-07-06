#include "lys.hpp"

#include <SDL\SDL_main.h>
#include <GL\glew.h>

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
			window.setSwapInterval(1);
			window.setVisible(true);

			glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

			timer.reset();

			bool running = true;
			while (running)
			{
				while (window.pollMessages(message))
				{
					if (message == WindowMessage::CLOSE) running = false;
					if (!running) break;
				}
				if (!running) continue;

				timer.update();
				LYS_LOG("%f", time.current);

				glClear(GL_COLOR_BUFFER_BIT);
				window.swapBuffers();
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