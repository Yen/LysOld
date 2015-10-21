#pragma once

#include <string>

#include "..\uielement.hpp"
#include "..\..\..\texture2d.hpp"

namespace lys
{

	class UITexture : public UIElement
	{
	private:
		Texture2D _texture;
	public:
		UITexture(const Vector2 &size, const Alignment &alignment, const Vector2 &offset, const std::string &path);
	};

}