#pragma once

#include <vector>

#include "..\maths.hpp"

namespace lys
{

	class Pixmap
	{
	public:
		enum Format : unsigned char
		{
			RGB,
			RGBA
		};
		typedef unsigned char Depth;
	private:
		Metric2 _size;
		std::vector<unsigned char> _data;
		Format _format;
		Depth _depth;
	public:
		Pixmap(const std::string &path);

		const Metric2 &getSize() const;
		const std::vector<unsigned char> &getData() const;
		const Format &getFormat() const;
		const Depth &getDepth() const;
	};

}