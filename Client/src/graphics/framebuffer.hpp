#pragma once

#include <GL\glew.h>

#include "..\maths.hpp"

namespace lys
{

	class FrameBuffer
	{
	private:
		GLuint _id;
		GLuint _depth;
		GLuint _texture;
		Metric2 _size;
	public:
		FrameBuffer(const Metric2 &size);
		~FrameBuffer();

		void bind() const;
		void bindTexture() const;
		const Metric2 &getSize() const;
		void setSize(const Metric2 &size);

		static void bindScreen();
	};

}