#include "uilayer.hpp"

#include "..\..\..\utils.hpp"

namespace lys
{

	UILayer::UILayer(const GraphicsProfile &profile)
		: _maxTextures(profile.getMaxTextureSlots()),
		_shader([&]() -> ShaderProgram
	{
		std::vector<ShaderData> shaders;
		shaders.push_back(ShaderData(GL_VERTEX_SHADER, ShaderProgram::createShaderList(utils::readFile("data/shaders/uilayer-v.glsl"))));

		ShaderDefines defines;
		defines["SHADER_COUNT"] = std::to_string(_maxTextures);

		shaders.push_back(ShaderData(GL_FRAGMENT_SHADER, ShaderProgram::createShaderList(ShaderProgram::processShaderSource(utils::readFile("data/shaders/uilayer-f.glsl"), defines))));
		return ShaderProgram(shaders);
	}()),
		_textures(_maxTextures)
	{
		std::vector<int> textureIDs(_maxTextures);
		for (int i = 0; i < _maxTextures; i++)
		{
			textureIDs[i] = i;
		};
		_shader.enable();
		_shader.setUniform1iv("uni_textures", _maxTextures, textureIDs.data());

		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);

		glGenBuffers(1, &_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

		glBufferData(GL_ARRAY_BUFFER, LYS_UILAYER_BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(LYS_UILAYER_SHADER_POSITION);
		glEnableVertexAttribArray(LYS_UILAYER_SHADER_UV);
		glEnableVertexAttribArray(LYS_UILAYER_SHADER_TID);
		glEnableVertexAttribArray(LYS_UILAYER_SHADER_TFORMAT);
		glEnableVertexAttribArray(LYS_UILAYER_SHADER_COLOR);

		glVertexAttribPointer(LYS_UILAYER_SHADER_POSITION, 3, GL_FLOAT, GL_FALSE, LYS_UILAYER_VERTEX_DATA_SIZE, (const GLvoid *)(offsetof(VertexData, position)));
		glVertexAttribPointer(LYS_UILAYER_SHADER_UV, 2, GL_FLOAT, GL_FALSE, LYS_UILAYER_VERTEX_DATA_SIZE, (const GLvoid *)(offsetof(VertexData, uv)));
		glVertexAttribPointer(LYS_UILAYER_SHADER_TID, 1, GL_FLOAT, GL_FALSE, LYS_UILAYER_VERTEX_DATA_SIZE, (const GLvoid *)(offsetof(VertexData, tid)));
		glVertexAttribPointer(LYS_UILAYER_SHADER_TFORMAT, 1, GL_FLOAT, GL_FALSE, LYS_UILAYER_VERTEX_DATA_SIZE, (const GLvoid *)(offsetof(VertexData, tformat)));
		glVertexAttribPointer(LYS_UILAYER_SHADER_COLOR, 4, GL_FLOAT, GL_FALSE, LYS_UILAYER_VERTEX_DATA_SIZE, (const GLvoid *)(offsetof(VertexData, color)));

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

	const float &UILayer::getRatio() const
	{
		return _ratio;
	}

	const Vector2 &UILayer::getSize() const
	{
		return _ratioSize;
	}

	Vector2 UILayer::mouseToView(const Metric2 &mousePosition) const
	{
		return Vector2((float)mousePosition.x / _ratio, (float)mousePosition.y / _ratio);
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

		glEnable(GL_BLEND);
		glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

		GLsizei batchCount = 0;
		GLsizei textureCount = 0;

		begin();

		_shader.enable();

		while (!_elements.empty())
		{
			auto &element = _elements.front();

			parseElement(batchCount, textureCount, element, _ratioSize, Vector2(0, 0));

			_elements.pop_front();
		}

		end();
		drawCall(batchCount, textureCount);
	}

	Vector2 UILayer::calculateTopLeft(const UIElement *element, const Vector2 &size, const Vector2 &topLeft)
	{
		switch (element->alignment)
		{
		case UIElement::Alignment::TOP_LEFT:
			return topLeft + element->offset;
			break;
		case UIElement::Alignment::TOP_RIGHT:
			return Vector2(topLeft.x + size.x - element->size.x - element->offset.x, topLeft.y + element->offset.y);
			break;
		case UIElement::Alignment::BOTTOM_RIGHT:
			return Vector2(topLeft.x + size.x - element->size.x - element->offset.x, topLeft.y + size.y - element->size.y - element->offset.y);
			break;
		case UIElement::Alignment::BOTTOM_LEFT:
			return Vector2(topLeft.x + element->offset.x, topLeft.y + size.y - element->size.y - element->offset.y);
			break;
		default:
			throw std::exception("UILayer failed to render a UIElement due to an invalid alignment");
			break;
		}
	}

	void UILayer::parseElement(GLsizei &batchCount, GLsizei &textureCount, const UIElement *element, const Vector2 &size, const Vector2 &topLeft)
	{
		Vector2 localTopLeft = calculateTopLeft(element, size, topLeft);

		if (element->content)
		{

			float tid = -1.4f;
			float tformat = 0.0f;
			auto &tex = element->texture;

			if ((batchCount >= LYS_UILAYER_MAX_ELEMENTS) || ((tex != nullptr) && (textureCount >= _maxTextures)))
			{
				end();
				drawCall(batchCount, textureCount);
				begin();

				batchCount = 0;
				textureCount = 0;
			}

			if (tex != nullptr)
			{
				tid = ((float)textureCount) + 0.4f;
				tformat = ((float)tex->getPixmapInformation().format) + 0.4f;
				_textures[textureCount++] = tex;
			}

			_buffer[0].uv = element->uvs[0];
			_buffer[1].uv = element->uvs[1];
			_buffer[2].uv = element->uvs[2];
			_buffer[3].uv = element->uvs[3];

			_buffer[0].position = Vector3(localTopLeft, 0);
			_buffer[1].position = Vector3(localTopLeft.x + element->size.x, localTopLeft.y, 0);
			_buffer[2].position = Vector3(localTopLeft + element->size, 0);
			_buffer[3].position = Vector3(localTopLeft.x, localTopLeft.y + element->size.y, 0);

			_buffer[0].tid = tid;
			_buffer[1].tid = tid;
			_buffer[2].tid = tid;
			_buffer[3].tid = tid;

			_buffer[0].tformat = tformat;
			_buffer[1].tformat = tformat;
			_buffer[2].tformat = tformat;
			_buffer[3].tformat = tformat;

			_buffer[0].color = element->color;
			_buffer[1].color = element->color;
			_buffer[2].color = element->color;
			_buffer[3].color = element->color;

			_buffer += 4;

			batchCount++;
		}

		for (size_t i = 0; i < element->getChildrenCount(); i++)
		{
			parseElement(batchCount, textureCount, element->getChildren()[i], element->size, localTopLeft);
		}
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

	void UILayer::drawCall(const GLsizei &batchCount, const GLsizei &textureCount)
	{
		for (GLsizei i = 0; i < textureCount; i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			_textures[i]->bind();
		}

		glBindVertexArray(_vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);

		glDrawElements(GL_TRIANGLES, batchCount * 6, LYS_UILAYER_INDICES_TYPE, nullptr);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void UILayer::resize(const Metric2 &size)
	{
		if ((size.x > 0) && (size.y > 0))
			if (size.x < size.y)
			{
				_ratio = (float)size.x / (float)LYS_UILAYER_RATIO_SIZE;
				_ratioSize = Vector2(LYS_UILAYER_RATIO_SIZE, (float)size.y / _ratio);
			}
			else
			{
				_ratio = (float)size.y / (float)LYS_UILAYER_RATIO_SIZE;
				_ratioSize = Vector2((float)size.x / _ratio, LYS_UILAYER_RATIO_SIZE);
			}

		_shader.enable();
		_shader.setUniformMat4("uni_pr_matrix", Matrix4::orthographic(0, _ratioSize.x, _ratioSize.y, 0, -1, 100));
	}

}