/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_features.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 13:19:15 by sdarius-          #+#    #+#             */
/*   Updated: 2026/09/28 14:01:00 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuple.h"
#include <math.h>
void	nega_tup(t_tuple *arr)
{
	arr->x *= -1;
	arr->y *= -1;
	arr->z *= -1;
	arr->w *= -1;
}

void	multy_tup(t_tuple *arr, double x)
{
	arr->x *= x;
	arr->y *= x;
	arr->z *= x;
	arr->w *= x;
}

t_tuple	subst_tup(t_tuple arr, t_tuple arr2)
{
	t_tuple	new_arr;

	new_arr.x = arr.x - arr2.x;
	new_arr.y = arr.y - arr2.y;
	new_arr.z = arr.z - arr2.z;
	new_arr.w = fabs((arr.w - arr2.w));
	return (new_arr);
}

t_tuple	add_tup(t_tuple arr, t_tuple arr2)
{
	t_tuple	new_arr;

	new_arr.x = arr.x + arr2.x;
	new_arr.y = arr.y + arr2.y;
	new_arr.z = arr.z + arr2.z;
	if (arr.w == 1 || arr2.w == 1)
		new_arr.w = 1;
	else
		new_arr.w = 0;
	return (new_arr);
}
