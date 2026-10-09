/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_features_5.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 10:16:09 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/09 10:16:36 by sdarius-         ###   ########.fr       */
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
		return (true); /* parallel to the cap */
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
