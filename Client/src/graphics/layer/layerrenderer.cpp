#include "layerrenderer.hpp"

#include "..\..\logic\engine.hpp"

namespace lys
{

	LayerRenderer::LayerData::LayerData(LayerInterface *&layer, const Vector2 &elementSize, const Metric2 &size)
		: layer(layer),
		buffer(size),
		element(elementSize, UIElement::TOP_LEFT, Vector2(0, 0), &buffer.getTexture())
	{}

	LayerRenderer::LayerRenderer(EngineInternals &internals)
		: _ui(internals.profile)
	{
		resize(internals.window.getSize());
	}

	void LayerRenderer::add(LayerInterface *layer)
	{
		_layers.emplace_back(layer, _ui.getSize(), _size);
	}

	void LayerRenderer::remove(LayerInterface *layer)
	{
		for (size_t i = 0; i < _layers.size(); i++)
		{
			if (_layers[i].layer == layer)
			{
				_layers.erase(_layers.begin() + i);
				return;
			}
		}
	}

	void LayerRenderer::render()
	{
		//TODO: Strange issues with alpha values in framebuffers, will just be rendered to the screen
		//until the problem is solved
		for (auto &layer : _layers)
		{
			//layer.buffer.bind();
			//layer.buffer.clear();
			layer.layer->flush();
			//layer.buffer.getTexture().bind();
			//layer.buffer.getTexture().generateMipmap();

			//_ui.push(layer.element);
		}

		//FrameBuffer::unbind();
		//_ui.flush();
	}

	void LayerRenderer::resize(const Metric2 &size)
	{
		_size = size;

		_ui.resize(_size);
		for (auto &layer : _layers)
		{
			layer.element.size = _ui.getSize();
			layer.buffer.getTexture().setData(nullptr, Pixmap::Information(_size, Pixmap::Information::RGBA, 32));
			layer.buffer.resize(_size);
		}
	}

}