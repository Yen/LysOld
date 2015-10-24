#pragma once

#include <vector>

#include "..\maths.hpp"

namespace lys
{

	class Pixmap
	{
	public:
		class Information
		{
		public:
			enum Format : unsigned char
			{
				ALPHA = 0,
				RGB = 1,
				RGBA = 2
			};
			typedef unsigned char Depth;
		public:
			Metric2 size;
			Format format;
			Depth depth;
		public:
			Information() = default;
			Information(const Metric2 &size, const Format &format, const Depth &depth);

			bool operator ==(const Information &other) const;
			bool operator !=(const Information &other) const;
		};
	private:
		std::vector<unsigned char> _data;
		Information _information;
	public:
		Pixmap(const std::string &path);

		const std::vector<unsigned char> &getData() const;
		const Information &getInformation() const;
	};

}