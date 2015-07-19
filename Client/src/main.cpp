#include <SDL2\SDL_main.h>

#include "lys.hpp"
#include "logic\engine.hpp"

namespace lys
{

	int run()
	{
		try
		{
			Engine engine;
			engine.run();
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