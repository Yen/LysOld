#include "uielement.hpp"

#include <vector>

namespace lys
{

	UIElement::UIElement(const Vector2 &size, const Alignment &alignment, const Vector2 &offset)
		: size(size), alignment(alignment), offset(offset), uvs{ Vector2(0, 1), Vector2(1, 1), Vector2(1, 0), Vector2(0, 0) }
	{}

	const UIElement *UIElement::getChildren() const
	{
		return nullptr;
	}

	size_t UIElement::getChildrenCount() const
	{
		return 0;
	}

	const Texture2D *UIElement::getTexture() const
	{
		return nullptr;
	}

}