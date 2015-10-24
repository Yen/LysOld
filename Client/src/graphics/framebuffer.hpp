#pragma once

#include <GL\glew.h>

#include "texture2d.hpp"

namespace lys
{

	class FrameBuffer
	{
	private:
		GLuint _id;
		GLuint _depthId;
		Texture2D _texture;
	public:
		FrameBuffer(const Metric2 &size);
		~FrameBuffer();

		Texture2D &getTexture();

		void clear() const;

		void bind() const;
		static void unbind();

		void resize(const Metric2 &size);
	};

}