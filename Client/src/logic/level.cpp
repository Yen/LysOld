#include "level.hpp"

namespace lys
{

	Level::Level()
		: Level(LYS_LEVEL_DEFAULT_UPS)
	{}

	Level::Level(const int &ups)
		: _ups(ups)
	{}

	const int &Level::getUPS() const
	{
		return _ups;
	}

	Level::~Level()
	{
		return;
	}

	void Level::resize(Window &window)
	{
		return;
	};

}