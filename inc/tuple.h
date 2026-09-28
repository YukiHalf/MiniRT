/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 13:19:49 by sdarius-          #+#    #+#             */
/*   Updated: 2026/09/28 13:58:01 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TUPLE_H
# define TUPLE_H

# include "libft.h"

typedef enum e_tuples_enum
{
	VECTOR,
	POINT
}			t_tuple_enum;

typedef struct tuple_s
{
	double	x;
	double	y;
	double	z;
	double	w;
}			t_tuple;

typedef struct projectile_s
{
	t_tuple	position;
	t_tuple	velocity;
}			t_projectile;

typedef struct enviroment_s
{
	t_tuple	gravity;
	t_tuple	wind;
}			t_enviroment;


/*creates and alocates a point and returns it's address*/
t_tuple		init_point(double x, double y, double z);
/*creates and alocates a vector and returns it's address*/
t_tuple		init_vector(double x, double y, double z);
/*creates a new array, that has the parameters as values*/
t_tuple		*create_tup(float a, float b, float c, float d);
/*checks if two float parameters are equal under a marign of error(epsilon)*/
bool		f_equality(float a, float b, float epsilon);
/*adds two arrays togherter while respecting the point,vector scenario*/
t_tuple		add_tup(t_tuple arr, t_tuple arr2);
/*substitutes two arrays togherter while respecting the point,vector scenario*/
t_tuple		subst_tup(t_tuple arr, t_tuple arr2);
/*negates a array*/
void		nega_tup(t_tuple *arr);
/*multiplies the arr with x uniformily*/
void		multy_tup(t_tuple *arr, double x);
/*divide the arr with x uniformily*/
void		div_tup(t_tuple *arr, double x);
/*find the magnitute of an array,
	this meand the distance you would have to travel*/
double		magn_tup(t_tuple arr);
/*We are taking an arbitrary vector and converting it into a unit vector.*/
t_tuple		norm_tup(t_tuple arr);
/*Dot function take stwo arr and returns a scalar value*/
double		dot_tup(t_tuple arr1, t_tuple arr2);
/*returns another vector instead of a scalar.*/
t_tuple		cross_arr(t_tuple arr1, t_tuple arr2);

#endif
