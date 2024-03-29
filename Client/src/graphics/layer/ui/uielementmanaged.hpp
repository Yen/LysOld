#pragma once

#include "uielement.hpp"
#include "uilayer.hpp"

namespace lys
{

	class EngineInternals;

	class UIElementManaged : public UIElement
	{
	public:
		UIElementManaged() = default;
		UIElementManaged(const Vector2 &size, const Alignment &alignment, const Vector2 &offset, const Texture2D *texture, const bool &content = true);

		virtual void repaint(EngineInternals &internals, const UILayer &ui) = 0;
	};

}