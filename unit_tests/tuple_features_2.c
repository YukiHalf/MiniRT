/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_features_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 13:19:26 by sdarius-          #+#    #+#             */
/*   Updated: 2026/09/28 13:19:40 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_lib.h"

tuple_t	init_point(double x, double y, double z)
{
	tuple_t	tup;

	tup.x = x;
	tup.y = y;
	tup.z = z;
	tup.w = POINT;
	return (tup);
}

tuple_t	init_vector(double x, double y, double z)
{
	tuple_t	tup;

	tup.x = x;
	tup.y = y;
	tup.z = z;
	tup.w = VECTOR;
	return (tup);
}

tuple_t	*create_tup(float a, float b, float c, float d)
{
	tuple_t	*arr;

	arr = malloc(sizeof(tuple_t));
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
