#pragma once

#include "..\..\..\maths.hpp"
#include "..\..\..\graphics\texture2d.hpp"

namespace lys
{

	class UIElement
	{
	public:
		//TODO: Implement other alignments into UILayer
		enum Alignment : unsigned char
		{
			TOP_LEFT = 0,
			//TOP = 1,
			TOP_RIGHT = 2,
			//RIGHT = 3,
			BOTTOM_RIGHT = 4,
			//BOTTOM = 5,
			BOTTOM_LEFT = 6,
			//LEFT = 7,
			//CENTER = 8,
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