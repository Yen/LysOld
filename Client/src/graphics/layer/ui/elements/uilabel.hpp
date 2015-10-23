#pragma once

#include "..\uielementmanaged.hpp"
#include "..\..\..\typeengine.hpp"

namespace lys
{

	class UILabel : public UIElementManaged
	{
	private:
		TypeEngine &_typeEngine;
		std::string _text;
		std::vector<UIElement> _elements;
		std::vector<UIElement *>_elementPointers;
		std::map<wchar_t, std::shared_ptr<Texture2D>> _textures;
		bool _fixed;
	public:
		UILabel(const Vector2 &size, const Alignment &alignment, const Vector2 &offset, TypeEngine &typeEngine, const bool &fixed = false, const std::string &text = std::string());

		void setText(const std::string &text);
		const std::string &getText() const;
		void setFixed(const bool &fixed);
		const bool &getFixed() const;

		void repaint(EngineInternals &internals, const UILayer &ui) override;

		const UIElement *const *getChildren() const override;
		size_t getChildrenCount() const override;
	};

}