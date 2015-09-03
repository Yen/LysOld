#include "menu.hpp"

#include <sstream>
#include <thread>

#include "..\logic\engine.hpp"

namespace lys
{

	Menu::Menu(const EngineLoadingArgs &args)
		: Level(args, 60), _test(Sprite(Vector3(10, 10, 0), Vector2(200, 200), Vector4(1, 1, 1, 1), &_tex)), _tex("data/images/spectrum.jpg"), _label(Vector3(0, 0, 1))
	{
		_label.getFont().setHeight(20);
		_label.repaint();
	}

	void Menu::update(EngineInternals &internals, EngineArgs &args)
	{
		std::stringstream ss;
		ss << "FPS: " << internals.counter.getFPS(args.time.current);
		_label.setText(ss.str());

		if (internals.window.getButton(SDL_BUTTON_LEFT))
		{
			auto mousepos = internals.window.getMouse();
			mousepos.y = internals.window.getSize().y - mousepos.y;
			if ((mousepos.x >= _test.position.x) && (mousepos.x <= _test.position.x + _test.size.x))
			{
				if ((mousepos.y >= _test.position.y) && (mousepos.y <= _test.position.y + _test.size.y))
				{
					LYS_LOG("a");
				}
			}
		}
	}

	void Menu::draw(EngineInternals &internals, EngineArgs &args)
	{
		_interface.submit(&_test);
		_interface.submit(&_label);

		_interface.renderBatch();
	}

	void Menu::resize(EngineInternals &internals)
	{
		_interface.resize(internals.window.getSize());
		_label.setPosition(Vector3(10, internals.window.getSize().y - (float)_label.getFont().getHeight() - 10, _label.getPosition().z));
	}

}