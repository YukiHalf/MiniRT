/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_features_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 13:19:20 by sdarius-          #+#    #+#             */
/*   Updated: 2026/09/28 13:19:36 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_lib.h"

t_tuple	cross_arr(t_tuple arr1, t_tuple arr2)
{
	t_tuple	new_tup;
	double	x;
	double	y;
	double	z;

	new_tup = init_vector(0, 0, 0);
	new_tup.x = (arr1.y * arr2.z) - (arr1.z * arr2.y);
	new_tup.y = (arr1.z * arr2.x) - (arr1.x * arr2.z);
	new_tup.z = (arr1.x * arr2.y) - (arr1.y * arr2.x);
	return (new_tup);
}

double	dot_tup(t_tuple arr1, t_tuple arr2)
{
	double	dot;

	dot += arr1.x * arr2.x;
	dot += arr1.y * arr2.y;
	dot += arr1.z * arr2.z;
	dot += arr1.w * arr2.w;
	return (dot);
}

t_tuple	norm_tup(t_tuple arr)
{
	double	magnitute;

	magnitute = magn_arr(arr);
	arr.x /= magnitute;
	arr.y /= magnitute;
	arr.z /= magnitute;
	arr.w /= magnitute;
	return (arr);
}

double	magn_tuple(t_tuple arr)
{
	double	magnitute;

	magnitute = sqrt((arr.x * arr.x) + (arr.y * arr.y) + (arr.z * arr.z)
			+ (arr.w * arr.w));
	return (magnitute);
}

void	div_tup(t_tuple *arr, float x)
{
	arr->x /= x;
	arr->y /= x;
	arr->z /= x;
	arr->w /= x;
}
