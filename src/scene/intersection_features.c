/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_features.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 11:54:20 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/02 14:45:17 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_intersections init_intersections(void)
{
	return((t_intersections){0});
}
bool add_intersection(t_intersections *xs,t_intersection value)
{
	t_intersection *new_items;
	size_t new_capacity;

	if(xs->count == xs->capacity)
	{
		if(xs->capacity == 0)
			xs->capacity = 8;
		else
			new_capacity = xs->capacity * 2;
	}
}
