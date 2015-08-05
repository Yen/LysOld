#include "menu.hpp"

#include <sstream>

namespace lys
{

	Menu::Menu()
		: Level(60), _test(Sprite(Vector3(10, 10, 0), Vector2(200, 200), Vector4(1, 1, 1, 1), &_tex)), _tex("data/images/spectrum.jpg"), _label("ayy", Vector3(250, 250, 1))
	{
		_label.getFont().setHeight(400);
		_label.repaint();
	}

	void Menu::update(Window &window, const FixedTimerData &time)
	{
		std::stringstream ss;
		ss << time.current;
		_label.setText(ss.str());

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
		_interface.submit(&_label);

		_interface.renderBatch();
	}

	void Menu::resize(Window &window)
	{
		_interface.resize(window.getSize());
	}

}