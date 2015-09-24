#include "framebuffer.hpp"

#include <sstream>

namespace lys
{

	FrameBuffer::FrameBuffer(const Metric2 &size)
		: _size(size)
	{
		glGenFramebuffers(1, &_id);
		glBindFramebuffer(GL_FRAMEBUFFER, _id);

		glGenTextures(1, &_texture);
		glBindTexture(GL_TEXTURE_2D, _texture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _size.x, _size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glGenRenderbuffers(1, &_depth);
		glBindRenderbuffer(GL_RENDERBUFFER, _depth);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, _size.x, _size.y);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depth);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, _texture, 0);
		GLenum buffers[1] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, buffers);

		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (status != GL_FRAMEBUFFER_COMPLETE)
		{
			std::stringstream err;
			err << "Error creating framebuffer [" << status << "]";
			throw std::exception(err.str().data());
		}

		glBindTexture(GL_TEXTURE_2D, 0);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	FrameBuffer::~FrameBuffer()
	{
		glDeleteTextures(1, &_texture);
		glDeleteFramebuffers(1, &_id);
	}

	void FrameBuffer::bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _id);
		glViewport(0, 0, _size.x, _size.y);
	}

	void FrameBuffer::bindTexture() const
	{
		glBindTexture(GL_TEXTURE_2D, _texture);
	}

	const Metric2 &FrameBuffer::getSize() const
	{
		return _size;
	}

	void FrameBuffer::setSize(const Metric2 &size)
	{
		_size = size;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _size.x, _size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	}

	void FrameBuffer::bindScreen()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

}