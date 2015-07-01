#include "lys.hpp"

#include "maths.hpp"

int main()
{
	LYS_LOG("Lys");

	lys::Metric2 a;
	lys::Metric2 b(5, 10);

	lys::Metric3 c;
	lys::Metric3 d(b, 15);
	lys::Metric3 e(5, 10, 15);

	system("pause");

	return 0;
}