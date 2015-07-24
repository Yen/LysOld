#include "menu.hpp"

namespace lys
{

	Menu::Menu()
		: _test(Sprite(Vector3(10, 10, 0), Vector2(200, 200)))
	{

	}

	void Menu::update(Window &window, const FixedTimerData &time)
	{

	}

	void Menu::draw(Window &window, const FixedTimerData &time)
	{
		_interface.submit(&_test);

		_interface.renderBatch();
	}

	void Menu::resize(Window &window)
	{
		_interface.resize(window.getSize());
	}

}