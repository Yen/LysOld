#include "uitexture.hpp"

namespace lys
{

	UITexture::UITexture(const Vector2 &size, const Alignment &alignment, const Vector2 &offset, const std::string &path)
		: UIElement(size, alignment, offset, &_texture), _texture(Pixmap(path))
	{}

}