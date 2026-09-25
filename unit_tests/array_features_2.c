#include "test_lib.h"


float	*div_arr(float *arr, float x)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		arr[i] = arr[i] / x;
		i++;
	}
	return (arr);
}
