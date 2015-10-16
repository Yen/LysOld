#pragma once

#include <string>

#include "..\uielement.hpp"
#include "..\..\..\texture2d.hpp"

namespace lys
{

	class SimpleImageElement : public UIElement
	{
	private:
		Texture2D _texture;
		UIElement _test;
	public:
		SimpleImageElement(const Vector2 &size, const Alignment &alignment, const Vector2 &offset, const std::string &path);
	
		const Texture2D *getTexture() const override;

		const UIElement *getChildren() const override;
		size_t getChildrenCount() const override;
	};

}