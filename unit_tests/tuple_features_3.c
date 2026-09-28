#include "test_lib.h"

tuple_t *cross_arr(tuple_t *arr1,tuple_t *arr2)
{
	tuple_t *new_tup;
	double x;
	double y;
	double z;

	new_tup = init_vector(0,0,0);

	new_tup->x  = (arr1->y * arr2->z) - (arr1->z * arr2->y);
	new_tup->y  = (arr1->z * arr2->x) - (arr1->x * arr2->z);
	new_tup->z  = (arr1->x * arr2->y) - (arr1->y * arr2->x);
	return (new_tup);
}


double dot_tup(tuple_t *arr1,tuple_t *arr2)
{
	double dot;


	dot += arr1->x * arr2->x;
	dot += arr1->y * arr2->y;
	dot += arr1->z * arr2->z;
	dot += arr1->w * arr2->w;
	return dot;
}



tuple_t*  norm_tup(tuple_t *arr)
{
	double magnitute;

	magnitute = magn_arr(arr);
	arr->x /= magnitute;
	arr->y /= magnitute;
	arr->z /= magnitute;
	arr->w /= magnitute;
	return(arr);
}


double magn_tuple(tuple_t *arr)
{
	double magnitute;

	magnitute = sqrt((arr->x * arr->x) + (arr->y * arr->y)+(arr->z * arr->z)+(arr->w * arr->w));
	return (magnitute);
}


void	div_tup(tuple_t *arr, float x)
{
	arr->x /= x;
	arr->y /= x;
	arr->z /= x;
	arr->w /= x;
}
