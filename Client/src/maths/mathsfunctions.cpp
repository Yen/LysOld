#include "mathsfunctions.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

namespace lys
{

	namespace maths
	{

		float toRadians(const float &degrees)
		{
			return (float)(degrees * (M_PI / 180.0));
		}

		float toDegrees(const float &radians)
		{
			return (float)(radians * (180.0 / M_PI));
		}

		int sign(const float &value)
		{
			return (value > 0) - (value < 0);
		}

	}

}