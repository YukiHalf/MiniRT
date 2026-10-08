/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 13:19:37 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/08 13:19:39 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

bool	intersect_world(const t_rt_scene *world, const t_ray *ray,
		t_intersections *xs)
{
	int	i;

	i = 0;
	while (i < world->object_count)
	{
		if (!intersect(xs, &world->objects[i], ray))
			return (false);
		i++;
	}
	return (true);
}

t_comps	prepare_computations(const t_intersection *intersection, t_ray ray)
{
	t_comps	comps;

	comps.t = intersection->t;
	comps.object = intersection->t_object;
	comps.point = ray_position(ray, comps.t);
	comps.normalv = normal_at(*comps.object, comps.point);
	comps.over_point = add_tup(comps.point, multy_tup_return(comps.normalv,
				EPSILON));
	comps.eyev = nega_tup_return(ray.direction);
	comps.inside = false;
	if (dot_tup(comps.normalv, comps.eyev) < 0)
	{
    comps.inside = true;
		comps.normalv = nega_tup_return(comps.normalv);
	}
  comps.over_point = add_tup(comps.point, multy_tup_return(comps.normalv, EPSILON));
	return (comps);
}
