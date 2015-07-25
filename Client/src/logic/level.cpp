#include "level.hpp"

namespace lys
{

	Level::Level()
		: Level(LYS_LEVEL_DEFAULT_UPS)
	{}

	Level::Level(const int &ups)
		: _ups(ups)
	{}

	Level::~Level()
	{}

	const unsigned int &Level::getUPS() const
	{
		return _ups;
	}

	void Level::update(Window &window, const FixedTimerData &time)
	{}

	void Level::resize(Window &window)
	{};

}