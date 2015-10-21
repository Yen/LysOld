#pragma once

#include "..\..\..\maths.hpp"
#include "..\..\..\graphics\texture2d.hpp"

namespace lys
{

	class UIElement
	{
	public:
		enum Alignment : char
		{
			TOP_LEFT,
			TOP,
			TOP_RIGHT,
			RIGHT,
			BOTTOM_RIGHT,
			BOTTOM,
			BOTTOM_LEFT,
			LEFT,
			CENTER,
		};
	public:
		Vector2 size;
		Alignment alignment;
		Vector2 offset;
		Vector2 uvs[4];
		const Texture2D *texture;
		bool content;
	public:
		UIElement() = default;
		UIElement(const Vector2 &size, const Alignment &alignment, const Vector2 &offset, const Texture2D *texture, const bool &content = true);

		virtual const UIElement *const *getChildren() const;
		virtual size_t getChildrenCount() const;
	};

}