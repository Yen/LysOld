#pragma once

#include "..\uielementmanaged.hpp"

namespace lys
{
	class UIProgressBar : public UIElementManaged
	{
	private:
		UIElement _bar;
		UIElement *_barPointer = &_bar;
		float _progress;
	public:
		UIProgressBar(const Vector2 &size, const Alignment &alignment, const Vector2 &offset);

		void setProgress(const float &progress);
		const float &getProgress() const;

		void setBarColor(const Vector4 &color);
		const Vector4 &getBarColor() const;

		void repaint(EngineInternals &internals, const UILayer &ui) override;

		const UIElement *const *getChildren() const override;
		size_t getChildrenCount() const override;
	};
}