#ifndef TEST_LIB_H
#define TEST_LIB_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "../inc/libft/libft.h"

typedef enum e_tuples_enum
{
	VECTOR,
	POINT
} t_tuple_enum;

typedef struct tuple_s{
	double x;
	double y;
	double z;
	double w;
} tuple_t;


typedef struct projectile_s{
	tuple_t position;
	tuple_t velocity;
}projectile_t;

typedef struct enviroment_s{
	tuple_t gravity;
	tuple_t wind;
}enviroment_t;





/*creates and alocates a point and returns it's address*/
tuple_t init_point(double x, double y, double z);
/*creates and alocates a vector and returns it's address*/
tuple_t init_vector(double x, double y, double z);
/*creates a new array, that has the parameters as values*/
tuple_t	*create_tup(float a, float b, float c, float d);
/*checks if two float parameters are equal under a marign of error(epsilon)*/
bool	f_equality(float a, float b, float epsilon);
/*adds two arrays togherter while respecting the point,vector scenario*/
tuple_t	add_tup(tuple_t arr, tuple_t arr2);
/*substitutes two arrays togherter while respecting the point,vector scenario*/
tuple_t	subst_tup(tuple_t arr, tuple_t arr2);
/*negates a array*/
void	nega_tup(tuple_t *arr);
/*multiplies the arr with x uniformily*/
void	multy_tup(tuple_t  *arr, float x);
/*/*divide the arr with x uniformily*/
void	div_tup(tuple_t *arr, float x);
/*find the magnitute of an array, this meand the distance you would have to travel*/
double magn_tuple(tuple_t *arr);
/*We are taking an arbitrary vector and converting it into a unit vector.*/
tuple_t*  norm_tup(tuple_t *arr);
/*Dot function take stwo arr and returns a scalar value*/
double dot_tup(tuple_t *arr1,tuple_t *arr2);
/*returns another vector instead of a scalar.*/
tuple_t *cross_arr(tuple_t *arr1,tuple_t *arr2);



#endif
