#include "layerrenderer.hpp"

namespace lys
{

	void LayerRenderer::add(LayerInterface *layer)
	{
		_layers.emplace_back(layer);
	}

	void LayerRenderer::remove(LayerInterface *layer)
	{
		for (size_t i = 0; i < _layers.size(); i++)
		{
			if (_layers[i] == layer)
			{
				_layers.erase(_layers.begin() + i);
				return;
			}
		}
	}

	void LayerRenderer::render()
	{
		for (auto &layer : _layers)
		{
			layer->flush();
		}
	}

}