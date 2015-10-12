#include "framebuffer.hpp"

namespace lys
{

	FrameBuffer::FrameBuffer(const Metric2 &size)
		: _texture(nullptr, Pixmap::Information(size, Pixmap::Information::Format::RGBA, 32))
	{
		glGenFramebuffers(1, &_id);
		glBindFramebuffer(GL_FRAMEBUFFER, _id);

		_texture.bind();

		glGenRenderbuffers(1, &_depthId);
		glBindRenderbuffer(GL_RENDERBUFFER, _depthId);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, size.x, size.y);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthId);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture._id, 0);

		GLenum db[1] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, db);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			throw std::exception("Error creating FrameBuffer");
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	FrameBuffer::~FrameBuffer()
	{
		glDeleteRenderbuffers(1, &_depthId);
		glDeleteFramebuffers(1, &_id);
	}

	const Texture2D &FrameBuffer::getTexture() const
	{
		return _texture;
	}

	void FrameBuffer::clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void FrameBuffer::bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _id);
		glViewport(0, 0, _texture.getPixmapInformation().size.x, _texture.getPixmapInformation().size.y);
	}

	void FrameBuffer::unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

}