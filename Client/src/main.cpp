#include "lys.hpp"

namespace lys
{

	int run()
	{
		try
		{
			// Program code
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

		LYS_LOG("No exceptions occured in run function");
		return 0;
	}

}

int main()
{
	LYS_LOG_APP("Lys");

	// Version checker or something

	LYS_LOG_APP("Executing run function");
	int execution = lys::run();
	LYS_LOG_APP("Run function complete, return code: (%d)", execution);

	// Clean up code?

	LYS_LOG_APP("Program reached exit point safely");

	LYS_PAUSE;

	return 0;
}