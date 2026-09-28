/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_features.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 13:19:15 by sdarius-          #+#    #+#             */
/*   Updated: 2026/09/28 13:19:38 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_lib.h"

void	nega_tup(tuple_t *arr)
{
	arr->x *= -1;
	arr->y *= -1;
	arr->z *= -1;
	arr->w *= -1;
}

void	multy_tup(tuple_t *arr, float x)
{
	arr->x *= x;
	arr->y *= x;
	arr->z *= x;
	arr->w *= x;
}

tuple_t	subst_tup(tuple_t arr, tuple_t arr2)
{
	tuple_t	new_arr;

	new_arr.x = arr.x - arr2.x;
	new_arr.y = arr.y - arr2.y;
	new_arr.z = arr.z - arr2.z;
	new_arr.w = fabs((arr.w - arr2.w));
	return (new_arr);
}

tuple_t	add_tup(tuple_t arr, tuple_t arr2)
{
	tuple_t	new_arr;

	new_arr.x = arr.x + arr2.x;
	new_arr.y = arr.y + arr2.y;
	new_arr.z = arr.z + arr2.z;
	if (arr.w == 1 || arr2.w == 1)
		new_arr.w = 1;
	else
		new_arr.w = 0;
	return (new_arr);
}
