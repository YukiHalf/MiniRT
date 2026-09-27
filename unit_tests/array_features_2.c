#include "test_lib.h"

float *norm_arr(float *arr)
{
	float magnitute;

	magnitute = magn_arr(arr);
	arr[0] = arr[0] / magnitute;
	arr[1] = arr[1] / magnitute;
	arr[2] = arr[2] / magnitute;
	arr[3] = arr[3] / magnitute;
	return (arr);
}


float magn_arr(float *arr)
{
	float magnitute;

	magnitute = sqrt((arr[0] * arr[0]) + (arr[1] * arr[1])+(arr[2] * arr[2])+(arr[3] * arr[3]));
	return (magnitute);
}


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
