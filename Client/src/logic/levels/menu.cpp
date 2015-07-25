#include "menu.hpp"

namespace lys
{

	Menu::Menu()
		: Level(60), _test(Sprite(Vector3(10, 10, 0), Vector2(200, 200), &_tex)), _tex("data/images/spectrum.jpg")
	{

	}

	void Menu::update(Window &window, const FixedTimerData &time)
	{
		if (window.getButton(SDL_BUTTON_LEFT))
		{
			auto mousepos = window.getMouse();
			mousepos.y = window.getSize().y - mousepos.y;
			if ((mousepos.x >= _test.position.x) && (mousepos.x <= _test.position.x + _test.size.x))
			{
				if ((mousepos.y >= _test.position.y) && (mousepos.y <= _test.position.y + _test.size.y))
				{
					LYS_LOG("a");
				}
			}
		}
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