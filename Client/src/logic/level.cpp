#include "level.hpp"

namespace lys
{

	Level::Level(EngineInternals &internals, const EngineLoadingArgs &args, const int &ups)
		: _ups(ups)
	{}

	const unsigned int &Level::getUPS() const
	{
		return _ups;
	}

	void Level::update(EngineInternals &internals, EngineArgs &args)
	{}

	void Level::resize(EngineInternals &internals)
	{};

}