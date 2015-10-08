#include "uilayer.hpp"

#include "..\..\..\utils.hpp"

namespace lys
{

	UILayer::UILayer(const GraphicsProfile &profile)
		: _shader([&]() -> ShaderProgram
	{
		std::vector<ShaderData> shaders;
		shaders.push_back(ShaderData(GL_VERTEX_SHADER, ShaderProgram::createShaderList(utils::readFile("data/shaders/uilayer-v.glsl"))));
		shaders.push_back(ShaderData(GL_FRAGMENT_SHADER, ShaderProgram::createShaderList(utils::readFile("data/shaders/uilayer-f.glsl"))));
		return ShaderProgram(shaders);
	}()),
		_maxTextures(profile.getMaxTextureSlots())
	{
		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);

		glGenBuffers(1, &_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

		glBufferData(GL_ARRAY_BUFFER, LYS_UILAYER_BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(LYS_UILAYER_SHADER_POSITION);
		glVertexAttribPointer(LYS_UILAYER_SHADER_POSITION, 3, GL_FLOAT, GL_FALSE, LYS_UILAYER_VERTEX_DATA_SIZE, (const GLvoid *)(offsetof(VertexData, position)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);

		UILayerIndice indices[LYS_UILAYER_INDICES_COUNT];

		UILayerIndice offset = 0;
		for (UILayerIndice i = 0; i < LYS_UILAYER_INDICES_COUNT; i += 6)
		{
			indices[i + 0] = offset + 0;
			indices[i + 1] = offset + 3;
			indices[i + 2] = offset + 1;

			indices[i + 3] = offset + 3;
			indices[i + 4] = offset + 2;
			indices[i + 5] = offset + 1;

			offset += 4;
		}

		glGenBuffers(1, &_ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(UILayerIndice) * LYS_UILAYER_INDICES_COUNT, indices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	UILayer::~UILayer()
	{
		glDeleteBuffers(1, &_ibo);
		glDeleteVertexArrays(1, &_vao);
		glDeleteBuffers(1, &_vbo);
	}

	void UILayer::push(UIElement &data)
	{
		_elements.push_back(&data);
	}

	void UILayer::flush()
	{
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);

		GLsizei batchCount = 0;

		begin();

		_shader.enable();
		while (!_elements.empty())
		{
			auto &element = _elements.front();

			_buffer[0].position = Vector3(element->offset, 0);
			_buffer[1].position = Vector3(element->offset.x + element->size.x, element->offset.y, 0);
			_buffer[2].position = Vector3(element->offset.x + element->size.x, element->offset.y + element->size.y, 0);
			_buffer[3].position = Vector3(element->offset.x, element->offset.y + element->size.y, 0);

			_buffer += 4;

			batchCount++;

			_elements.pop_front();
		}

		end();
		drawCall(batchCount);
	}

	void UILayer::begin()
	{
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		_buffer = (VertexData *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void UILayer::end()
	{
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void UILayer::drawCall(const GLsizei &batchCount)
	{
		glBindVertexArray(_vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);

		glDrawElements(GL_TRIANGLES, batchCount * 6, LYS_UILAYER_INDICES_TYPE, nullptr);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void UILayer::resize(const Metric2 &size)
	{
		_shader.enable();
		_shader.setUniformMat4("uni_pr_matrix", Matrix4::orthographic(0, (float)size.x, (float)size.y, 0, -1, 100));
	}

}