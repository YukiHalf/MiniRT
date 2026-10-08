/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 13:20:17 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/08 13:20:18 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

static bool	is_shadowed(t_tuple point, t_rt_scene *scene, t_intersections *xs)
{
	double			distance;
	t_tuple			shadow;
	t_ray			ray;
	t_intersection	*h;

	shadow = subst_tup(scene->lights[0].pos, point);
	distance = magn_tup(shadow);
	ray = init_ray(point, norm_tup(shadow));
	xs->count = 0;
	intersect_world(scene, &ray, xs);
	h = hit(xs);
	return (h != NULL && h->t < distance);
}

t_rgb	shade_hit(const t_rt_scene *world, t_comps comps, t_intersections *xs)
{
	t_lighting_parms	parms;

	parms.m = comps.object->material;
	parms.obj = comps.object;
	parms.l = world->lights[0];
	parms.pos = comps.point;
	parms.eyev = comps.eyev;
	parms.normalv = comps.normalv;
	parms.in_shadow = is_shadowed(comps.over_point, world, xs);
	return (lighting(parms));
}

t_rgb	color_at(const t_rt_scene *world, const t_ray *ray, t_intersections *xs)
{
	t_intersection	*intersection;
	t_comps			comps;

	xs->count = 0;
	if (!intersect_world(world, ray, xs))
		return ((t_rgb){0, 0, 0});
	intersection = hit(xs);
	if (!intersection)
		return ((t_rgb){0, 0, 0});
	comps = prepare_computations(intersection, *ray);
	return (shade_hit(world, comps, xs));
}
