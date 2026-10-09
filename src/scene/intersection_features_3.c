/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_features_3.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 13:46:42 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/09 10:19:20 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include <math.h>

bool	intersect(t_intersections *xs, t_object *shape, const t_ray *ray)
{
	t_ray	local_ray;

	local_ray = transform_ray(*ray, inverse_m4(shape->transform.m));
	return (local_intersect(xs, shape, &local_ray));
}

static void	check_axis(double origin, double direction, double minmax[2])
{
	double	tmin_numerator;
	double	tmax_numerator;
	double	tmp;

	tmin_numerator = (-1 - origin);
	tmax_numerator = (1 - origin);
	if (fabs(direction) >= EPSILON)
	{
		minmax[0] = tmin_numerator / direction;
		minmax[1] = tmax_numerator / direction;
	}
	else
	{
		minmax[0] = tmin_numerator * 1e30;
		minmax[1] = tmax_numerator * 1e30;
	}
	if (minmax[0] > minmax[1])
	{
		tmp = minmax[0];
		minmax[0] = minmax[1];
		minmax[1] = tmp;
	}
}

bool	cube_intersect(t_object *c, const t_ray *r, t_intersections *xs)
{
	double	minmax[2];
	double	xminmax[2];
	double	yminmax[2];
	double	zminmax[2];

	check_axis(r->origin.x, r->direction.x, xminmax);
	check_axis(r->origin.y, r->direction.y, yminmax);
	check_axis(r->origin.z, r->direction.z, zminmax);
	minmax[0] = fmax(xminmax[0], fmax(yminmax[0], zminmax[0]));
	minmax[1] = fmin(xminmax[1], fmin(yminmax[1], zminmax[1]));
	if (minmax[0] > minmax[1])
		return (true);
	if (!append_intersection(xs, minmax[0], c))
		return (false);
	return (append_intersection(xs, minmax[1], c));
}

bool	in_cap(const t_ray *r, double t)
{
	double	x;
	double	z;

	x = r->origin.x + t * r->direction.x;
	z = r->origin.z + t * r->direction.z;
	return (x * x + z * z <= 1.0);
}
