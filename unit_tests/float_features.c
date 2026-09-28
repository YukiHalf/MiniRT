#include "test_lib.h"


bool	f_equality(float a, float b, float epsilon)
{
	float	sum;

	//	printf("%f-%f=%f < %f STATE is %b\n", fabs(a), fabs(b), (fabs(a)
	//		- fabs(b)),
	//		epsilon,((fabs(a) - fabs(b)) < epsilon));
	sum = a - b;
	return (fabs(sum) < epsilon);
}

