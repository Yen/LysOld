#include "testelement.hpp"

#include <GL\glew.h>

namespace lys
{

	TestElement::TestElement(const Vector3 &position, const Vector2 &size)
		: _position(position), _size(size)
	{}

	void TestElement::draw(Window *window, const FixedTimerData &time)
	{
		glBegin(GL_QUADS);
		glVertex3f(_position.x, _position.y, _position.z);
		glVertex3f(_position.x + _size.x, _position.y, _position.z);
		glVertex3f(_position.x + _size.x, _position.y + _size.y, _position.z);
		glVertex3f(_position.x, _position.y + _size.y, _position.z);
		glEnd();
	}

}