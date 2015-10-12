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

		const Texture2D &getTexture() const;

		void clear() const;

		void bind() const;
		static void unbind();
	};

}