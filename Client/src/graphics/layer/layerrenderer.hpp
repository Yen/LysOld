#pragma once

#include <deque>

#include "layer.hpp"
#include "ui\uilayer.hpp"
#include "..\framebuffer.hpp"

namespace lys
{

	class EngineInternals;

	class LayerRenderer
	{
	private:
		struct LayerData
		{
		public:
			LayerInterface *layer;
			FrameBuffer buffer;
			UIElement element;
		public:
			LayerData(LayerInterface *&layer, const Vector2 &elementSize, const Metric2 &size);
		};
	private:
		//TODO: Replace LayerInterface * with a pair containing LayerInterface * and
		//some soft of framebuffer such that multisampling and filters can be applied
		//on a layer by layer basis
		std::deque<LayerData> _layers;
		UILayer _ui;
		Metric2 _size;
	public:
		LayerRenderer(EngineInternals &internals);
		void add(LayerInterface *layer);
		void remove(LayerInterface *layer);

		void render();

		void resize(const Metric2 &size);
	};

}