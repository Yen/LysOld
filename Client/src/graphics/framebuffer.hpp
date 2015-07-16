#pragma once

#include <GL\glew.h>

#include "texture.hpp"
#include "..\maths.hpp"

namespace lys
{

	class FrameBuffer
	{
	private:
		GLuint _id;
		GLuint _depthBuffer;
		Texture *_texture;
		Metric2 _size;
	public:
		FrameBuffer(const Metric2 &size);
		~FrameBuffer();

		void bind() const;
		static void unbind(const Metric2 &viewport);

		const Texture *getTexture() const;
	};

}