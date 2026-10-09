/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_features_5.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 10:16:09 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/09 10:24:29 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include <math.h>

static bool	intersect_cone_caps(t_object *cn, const t_ray *r,
		t_intersections *xs)
{
	double	t;
	double	x;
	double	z;

	if (fabs(r->direction.y) < EPSILON)
		return (true);
	t = (-cn->height - r->origin.y) / r->direction.y;
	x = r->origin.x + t * r->direction.x;
	z = r->origin.z + t * r->direction.z;
	if (x * x + z * z <= cn->height * cn->height && !append_intersection(xs, t,
			cn))
		return (false);
	return (true);
}

bool	cone_intersect(t_object *cn, const t_ray *r, t_intersections *xs)
{
	if (!intersect_cone_walls(cn, r, xs))
		return (false);
	return (intersect_cone_caps(cn, r, xs));
}

static t_tuple	cyl_helper(t_object shape, t_tuple local_point)
{
	if (fabs(local_point.y) < EPSILON)
		return (init_vector(0, -1, 0));
	if (fabs(local_point.y - shape.height) < EPSILON)
		return (init_vector(0, 1, 0));
	return (init_vector(local_point.x, 0, local_point.z));
}

static t_tuple	cube_helper(t_object shape, t_tuple local_point)
{
	double	maxc;

	maxc = fmax(fabs(local_point.x), fmax(fabs(local_point.y),
				fabs(local_point.z)));
	if (maxc == fabs(local_point.x))
		return (init_vector(local_point.x, 0, 0));
	else if (maxc == fabs(local_point.y))
		return (init_vector(0, local_point.y, 0));
	return (init_vector(0, 0, local_point.z));
}

t_tuple	local_normal_at(t_object shape, t_tuple local_point)
{
	double	maxc;

	if (shape.type == OBJ_SPHERE)
		return (subst_tup(local_point, shape.pos));
	if (shape.type == OBJ_PLANE)
		return (init_vector(0, 1, 0));
	if (shape.type == OBJ_CUBE)
		return (cube_helper(shape, local_point));
	if (shape.type == OBJ_CYLINDER)
		return (cyl_helper(shape, local_point));
	if (shape.type == OBJ_CONE)
	{
		if (fabs(local_point.y + shape.height) < EPSILON)
			return (init_vector(0, -1, 0));
		maxc = sqrt(powl(local_point.x, 2) + powl(local_point.z, 2));
		if (local_point.y > 0)
			maxc = -maxc;
		return (init_vector(local_point.x, maxc, local_point.z));
	}
	return (init_vector(0, 1, 0));
}
