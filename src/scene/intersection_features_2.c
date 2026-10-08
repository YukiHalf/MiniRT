/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_features_2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 13:20:47 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/08 10:46:23 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_intersection	*hit(t_intersections *xs)
{
	size_t			i;
	t_intersection	*lowest;

	i = 0;
	lowest = NULL;
	while (i < xs->count)
	{
		if (xs->items[i].t >= 0.0 && (lowest == NULL
				|| xs->items[i].t < lowest->t))
			lowest = &xs->items[i];
		i++;
	}
	return (lowest);
}

bool	local_intersect(t_intersections *xs, t_object *shape,
		const t_ray *local_ray)
{
	double	t;

	if (shape->type == OBJ_SPHERE)
		return (collect_sphere_intersections(xs, shape, local_ray));
	if (shape->type == OBJ_PLANE)
	{
		if (fabs(local_ray->direction.y) < EPSILON)
			return (true);
		t = -local_ray->origin.y / local_ray->direction.y;
		return (append_intersection(xs, t, shape));
	}
	return (false);
}
