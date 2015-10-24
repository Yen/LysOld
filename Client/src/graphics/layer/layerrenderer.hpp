#pragma once

#include <deque>

#include "layer.hpp"

namespace lys
{

	class LayerRenderer
	{
	private:
		//TODO: Replace LayerInterface * with a pair containing LayerInterface * and
		//some soft of framebuffer such that multisampling and filters can be applied
		//on a layer by layer basis
		std::deque<LayerInterface *> _layers;
	public:
		void add(LayerInterface *layer);
		void remove(LayerInterface *layer);

		void render();
	};

}