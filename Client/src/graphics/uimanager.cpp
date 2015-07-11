#include "uimanager.hpp"

#include "..\utils.hpp"

namespace lys
{

	UIManager::UIManager()
	{
		LYS_LOG("Creating new UIManager");

		std::vector<ShaderData> shaders;
		shaders.push_back(ShaderData(GL_VERTEX_SHADER, utils::readFile("data/shaders/ui.vert")));
		shaders.push_back(ShaderData(GL_FRAGMENT_SHADER, utils::readFile("data/shaders/ui.frag")));
		_shader = new ShaderProgram(shaders);
	}

	UIManager::~UIManager()
	{
		delete _shader;
	}

	void UIManager::push(UIElement *element)
	{
		_elements.push(element);
	}

	void UIManager::flush(Window *window, const FixedTimerData &time)
	{
		glEnable(GL_DEPTH_TEST);
		_shader->enable();

		while (!_elements.empty())
		{
			_elements.front()->draw(window, time);
			_elements.pop();
		}
	}

	void UIManager::resize(const Metric2 &size)
	{
		_shader->enable();
		_shader->setUniformMat4("uni_pr_matrix", Matrix4::orthographic(0, (float)size.x, 0, (float)size.y, -1, 100));
	}

}