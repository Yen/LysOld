#include "uiprogressbar.hpp"

namespace lys
{

	UIProgressBar::UIProgressBar(const Vector2 &size, const Alignment &alignment, const Vector2 &offset)
		: UIElementManaged(size, alignment, offset, nullptr, false),
		_bar(size, Alignment::BOTTOM_LEFT, Vector2(0, 0), nullptr)
	{}

	void UIProgressBar::setProgress(const float &progress)
	{
		_progress = progress;
	}

	const float &UIProgressBar::getProgress() const
	{
		return _progress;
	}

	void UIProgressBar::setBarColor(const Vector4 &color)
	{
		_bar.color = color;
	}

	const Vector4 &UIProgressBar::getBarColor() const
	{
		return _bar.color;
	}

	void UIProgressBar::repaint(EngineInternals &internals, const UILayer &ui)
	{
		_bar.size = Vector2(size.x * _progress, size.y);
	}

	const UIElement *const *UIProgressBar::getChildren() const
	{
		return &_barPointer;
	}

	size_t UIProgressBar::getChildrenCount() const
	{
		return 1;
	}

}