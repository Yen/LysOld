#include "uielementmanaged.hpp"

namespace lys
{

	UIElementManaged::UIElementManaged(const Vector2 &size, const Alignment &alignment, const Vector2 &offset, const Texture2D *texture, const bool &content)
		: UIElement(size, alignment, offset, texture, content)
	{}

}