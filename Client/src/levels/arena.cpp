#include "arena.hpp"

#include <sstream>

#include "..\logic\engine.hpp"
#include "..\graphics\texture2d.hpp"

namespace lys
{

	Arena::Arena(EngineInternals &internals, const EngineLoadingArgs &args)
		: Level(internals, args, 60),
		_ui(internals.profile),
		_fb(internals.window.getSize()),
		_test2(Vector2(20, 20), UIElement::Alignment::TOP_RIGHT, Vector2(5, 5), "data/images/spectrum.jpg"),
		_test3(Vector2(20, 20), UIElement::Alignment::BOTTOM_RIGHT, Vector2(5, 5), "data/images/spectrum.jpg"),
		_test4(Vector2(20, 20), UIElement::Alignment::BOTTOM_LEFT, Vector2(5, 5), "data/images/spectrum.jpg"),
		_label(Vector2(20, 2), UIElement::Alignment::TOP_LEFT, Vector2(0, 0), internals.typeEngine, false)
	{
	}

	void Arena::update(EngineInternals &internals, EngineArgs &args)
	{
		std::stringstream ss;
		const FPSInfo &fps = internals.counter.getFPS(args.time.current);
		ss << u8"FPS 幀率 帧率: " << fps.fps << " (" << fps.delay << ")";
		_label.setText(ss.str());
		_label.repaint(internals, _ui);
	}

	void Arena::draw(EngineInternals &internals, EngineArgs &args)
	{
		_ui.push(_test2);
		_ui.push(_test3);
		_ui.push(_test4);
		_ui.push(_label);
		_ui.flush();
	}

	void Arena::resize(EngineInternals &internals)
	{
		_ui.resize(internals.window.getSize());
		_label.repaint(internals, _ui);
	}

}