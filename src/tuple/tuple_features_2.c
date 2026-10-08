/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_features_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 13:19:26 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/08 13:17:31 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "tuple.h"

t_tuple	init_point(double x, double y, double z)
{
	t_tuple	tup;

	tup.x = x;
	tup.y = y;
	tup.z = z;
	tup.w = POINT;
	return (tup);
}

t_tuple	init_vector(double x, double y, double z)
{
	t_tuple	tup;

	tup.x = x;
	tup.y = y;
	tup.z = z;
	tup.w = VECTOR;
	return (tup);
}

t_tuple	*create_tup(float a, float b, float c, float d)
{
	t_tuple	*arr;

	arr = malloc(sizeof(t_tuple));
	if (!arr)
	{
		ft_putendl_fd("Malloc failed!", STDERR_FILENO);
		return (NULL);
	}
	arr->x = a;
	arr->y = b;
	arr->z = c;
	arr->w = d;
	return (arr);
}

t_tuple	nega_tup_return(t_tuple arr)
{
	return ((t_tuple){.x = -arr.x, .y = -arr.y, .z = -arr.z, .w = -arr.w});
}
