#include "uielement.hpp"

#include <vector>

namespace lys
{

	UIElement::UIElement(const Vector2 &size, const Alignment &alignment, const Vector2 &offset, const Texture2D *texture, const bool &content)
		: size(size),
		alignment(alignment),
		offset(offset),
		uvs{ Vector2(0, 1), Vector2(1, 1), Vector2(1, 0), Vector2(0, 0) },
		texture(texture),
		content(content),
		color(1, 1, 1, 1)
	{}

	const UIElement *const *UIElement::getChildren() const
	{
		return nullptr;
	}

	size_t UIElement::getChildrenCount() const
	{
		return 0;
	}

}