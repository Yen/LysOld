#include "testelement.hpp"

namespace lys
{

	TestElement::TestElement(const Vector3 &position, const Vector2 &size, const Vector4 &color, Texture *texture)
		: UIElement({ this->position = position, this->size = size, this->color = color, this->texture = texture })
	{}

}