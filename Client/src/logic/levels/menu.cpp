#include "menu.hpp"

#include <sstream>

namespace lys
{

	Menu::Menu()
		: Level(60), _test(Sprite(Vector3(10, 10, 0), Vector2(200, 200), Vector4(1, 1, 1, 1), &_tex)), _tex("data/images/spectrum.jpg"), _label(Vector3(0, 0, 1))
	{
		_label.getFont().setHeight(20);
		_label.repaint();
	}

	void Menu::update(EngineCore &core, const FixedTimerData &time)
	{
		std::stringstream ss;
		ss << "FPS: " << core.counter.getFPS(time.current);
		_label.setText(ss.str());

		if (core.window.getButton(SDL_BUTTON_LEFT))
		{
			auto mousepos = core.window.getMouse();
			mousepos.y = core.window.getSize().y - mousepos.y;
			if ((mousepos.x >= _test.position.x) && (mousepos.x <= _test.position.x + _test.size.x))
			{
				if ((mousepos.y >= _test.position.y) && (mousepos.y <= _test.position.y + _test.size.y))
				{
					LYS_LOG("a");
				}
			}
		}
	}

	void Menu::draw(EngineCore &core, const FixedTimerData &time)
	{
		_interface.submit(&_test);
		_interface.submit(&_label);

		_interface.renderBatch();
	}

	void Menu::resize(EngineCore &core)
	{
		_interface.resize(core.window.getSize());
		_label.setPosition(Vector3(10, core.window.getSize().y - (float)_label.getFont().getHeight() - 10, _label.getPosition().z));
	}

}