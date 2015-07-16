#include "framebuffer.hpp"

#include "..\lys.hpp"

namespace lys
{

	FrameBuffer::FrameBuffer(const Metric2 &size)
		: _size(size)
	{
		glGenFramebuffers(1, &_id);
		glGenRenderbuffers(1, &_depthBuffer);
		_texture = new Texture(size);

		glBindRenderbuffer(GL_RENDERBUFFER, _depthBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, _size.x, _size.y);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		glBindFramebuffer(GL_FRAMEBUFFER, _id);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthBuffer);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, _texture->getID(), 0);
		GLenum drawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, drawBuffers);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			throw std::exception("Error creating framebuffer");
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	FrameBuffer::~FrameBuffer()
	{
		delete _texture;
		glDeleteRenderbuffers(1, &_depthBuffer);
		glDeleteFramebuffers(1, &_id);
	}

	void FrameBuffer::bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _id);
		glViewport(0, 0, _size.x, _size.y);
	}

	void FrameBuffer::unbind(const Metric2 &viewport)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, viewport.x, viewport.y);
	}

	const Texture *FrameBuffer::getTexture() const
	{
		return _texture;
	}

}