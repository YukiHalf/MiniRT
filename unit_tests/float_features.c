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

int	is_tuple(float arr[4])
{
	float epsilon;

	epsilon = (float)1 / 1048576;
	printf("%f %f %f %f\n", arr[0], arr[1], arr[2], arr[3]);
	if (f_equality(arr[3], 0.0f, epsilon))
	{
		ft_putendl_fd("arr is a vector", STDOUT_FILENO);
		return (1);
	}
	else if (f_equality(arr[3], 1.0f, epsilon))
	{
		ft_putendl_fd("arr is a tuple", STDOUT_FILENO);
		return (0);
	}
	else
		ft_putendl_fd("Input INVALID", STDERR_FILENO);
	return (-1);
}