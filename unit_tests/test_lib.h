#ifndef TEST_LIB_H
#define TEST_LIB_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../libft/libft.h"

/*simple check function to check that input is a tuple or vector or invalid*/
int	is_tuple(float arr[4]);
/*creates a new array, that has the parameters as values*/
float *create_arr(float a,float b,float c, float d);
/*checks if two float parameters are equal under a marign of error(epsilon)*/
bool	f_equality(float a, float b, float epsilon);
/*adds two arrays togherter while respecting the point,vector scenario*/
float	*add_arrs(float *arr, float *arr2);
/*substitutes two arrays togherter while respecting the point,vector scenario*/
float	*subst_arr(float *arr, float *arr2);
/*negates a array*/
float 	*nega_arr(float *arr);
/*multiplies the arr with x uniformily*/
float	*multy_arr(float *arr, float x);
/*/*divide the arr with x uniformily*/*/
float	*div_arr(float *arr, float x)
#endif