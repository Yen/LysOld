#pragma once

#include "..\..\maths.hpp"

namespace lys
{

	class LayerInterface
	{
	public:
		virtual void flush() = 0;
	};

	template <typename T>
	class Layer : public LayerInterface
	{
	public:
		virtual void push(T &data) = 0;

		void pushArray(T *const &data, const size_t &count)
		{
			for (size_t i = 0; i < count; i++)
			{
				push(data[i]);
			}
		}
	};

}