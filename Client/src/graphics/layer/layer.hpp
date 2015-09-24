#pragma once

namespace lys
{

	template <typename T>
	class Layer
	{
	public:
		virtual void push(T &data) = 0;

		void pushArray(T *&data, const size_t &count)
		{
			for (size_t i = 0; i < count; i++)
			{
				push(data[i]);
			}
		}

		virtual void flush() = 0;
	};

}