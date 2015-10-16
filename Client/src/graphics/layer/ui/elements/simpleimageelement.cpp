#include "simpleimageelement.hpp"

namespace lys
{

	SimpleImageElement::SimpleImageElement(const Vector2 &size, const Alignment &alignment, const Vector2 &offset, const std::string &path)
		: UIElement(size, alignment, offset), _texture(Pixmap(path)), _test(Vector2(5, 5), UIElement::Alignment::BOTTOM_RIGHT, Vector2(5, 5))
	{}

	const Texture2D *SimpleImageElement::getTexture() const
	{
		return &_texture;
	}

	const UIElement *SimpleImageElement::getChildren() const
	{
		return &_test;
	}

	size_t SimpleImageElement::getChildrenCount() const
	{
		return 1;
	}

}