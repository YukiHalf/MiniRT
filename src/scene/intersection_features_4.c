/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_features_4.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 10:11:48 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/09 10:13:20 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include <math.h>


bool	intersect_caps(t_object *cy, const t_ray *r, t_intersections *xs)
{
	double	t;

	if (fabs(r->direction.y) < EPSILON)
		return (true); /* parallel to the caps */
	t = (0.0 - r->origin.y) / r->direction.y;
	if (in_cap(r, t) && !append_intersection(xs, t, cy))
		return (false);
	t = (cy->height - r->origin.y) / r->direction.y;
	if (in_cap(r, t) && !append_intersection(xs, t, cy))
		return (false);
	return (true);
}

bool	intersect_walls(t_object *cy, const t_ray *r, t_intersections *xs)
{
	double	a;
	double	b;
	double	c;
	double	disc;
	double	t[2];

	a = powl(r->direction.x, 2) + powl(r->direction.z, 2);
	if (a < EPSILON)
		return (true);
	b = 2.0 * (r->origin.x * r->direction.x + r->origin.z * r->direction.z);
	c = powl(r->origin.x, 2) + powl(r->origin.z, 2) - 1.0;
	disc = b * b - 4.0 * a * c;
	if (disc < 0.0)
		return (true);
	t[0] = (-b - sqrt(disc)) / (2.0 * a);
	t[1] = (-b + sqrt(disc)) / (2.0 * a);
	if (r->origin.y + t[0] * r->direction.y > 0.0 && r->origin.y + t[0]
		* r->direction.y < cy->height && !append_intersection(xs, t[0], cy))
		return (false);
	if (r->origin.y + t[1] * r->direction.y > 0.0 && r->origin.y + t[1]
		* r->direction.y < cy->height && !append_intersection(xs, t[1], cy))
		return (false);
	return (true);
}

bool	cylinder_intersect(t_object *cy, const t_ray *r, t_intersections *xs)
{
	if (!intersect_walls(cy, r, xs))
		return (false);
	return (intersect_caps(cy, r, xs));
}

bool	append_cone_hit(t_object *cn, const t_ray *r, t_intersections *xs,
		double t)
{
	double	y;

	y = r->origin.y + t * r->direction.y;
	if (y <= -cn->height || y >= 0.0)
		return (true);
	return (append_intersection(xs, t, cn));
}

bool	intersect_cone_walls(t_object *cn, const t_ray *r,
		t_intersections *xs)
{
	double	a;
	double	b;
	double	c;
	double	disc;
	double	t[2];

	a = powl(r->direction.x, 2) + powl(r->direction.z, 2) - powl(r->direction.y,
			2);
	b = 2.0 * (r->origin.x * r->direction.x + r->origin.z * r->direction.z
			- r->origin.y * r->direction.y);
	c = powl(r->origin.x, 2) + powl(r->origin.z, 2) - powl(r->origin.y, 2);
	if (fabs(a) < EPSILON && fabs(b) < EPSILON)
		return (true);
	disc = b * b - 4.0 * a * c;
	if (fabs(a) < EPSILON)
	{
		t[0] = -c / b;
		return (append_cone_hit(cn, r, xs, t[0]));
	}
	if (disc < 0.0)
		return (true);
	t[0] = (-b - sqrt(disc)) / (2.0 * a);
	t[1] = (-b + sqrt(disc)) / (2.0 * a);
	if (!append_cone_hit(cn, r, xs, t[0]))
		return (false);
	return (append_cone_hit(cn, r, xs, t[1]));
}
