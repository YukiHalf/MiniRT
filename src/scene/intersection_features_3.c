/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_features_3.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 13:46:42 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/08 13:13:51 by sdarius-         ###   ########.fr       */
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

t_tuple local_normal_at(t_object shape,t_tuple local_point)
{
  double maxc;

	if(shape.type == OBJ_SPHERE)
		return(subst_tup(local_point,shape.pos));
	if(shape.type == OBJ_PLANE)
		return(init_vector(0,1,0));
  if (shape.type == OBJ_CUBE)
  {
    maxc = fmax(fabs(local_point.x), fmax(fabs(local_point.y), fabs(local_point.z)));
    if (maxc == fabs(local_point.x))
      return init_vector(local_point.x, 0, 0);
    else if (maxc == fabs(local_point.y))
      return init_vector(0, local_point.y, 0);
    return init_vector(0, 0, local_point.z);
  }
  if (shape.type == OBJ_CYLINDER)
  {
    if (fabs(local_point.y) < EPSILON)
      return (init_vector(0, -1, 0));
    if (fabs(local_point.y - shape.height) < EPSILON)
      return (init_vector(0, 1, 0));
    return (init_vector(local_point.x, 0, local_point.z));
  }
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

static void check_axis(double origin, double direction, double minmax[2])
{
  double tmin_numerator;
  double tmax_numerator;
  double tmp;

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

bool  cube_intersect(t_object *c, const t_ray *r, t_intersections *xs)
{
  double minmax[2];
  double xminmax[2];
  double yminmax[2];
  double zminmax[2];

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

static bool	in_cap(const t_ray *r, double t)
{
	double	x;
	double	z;

	x = r->origin.x + t * r->direction.x;
	z = r->origin.z + t * r->direction.z;
	return (x * x + z * z <= 1.0);
}

static bool	intersect_caps(t_object *cy, const t_ray *r, t_intersections *xs)
{
	double	t;

	if (fabs(r->direction.y) < EPSILON)
		return (true);              /* parallel to the caps */
	t = (0.0 - r->origin.y) / r->direction.y;
	if (in_cap(r, t) && !append_intersection(xs, t, cy))
		return (false);
	t = (cy->height - r->origin.y) / r->direction.y;
	if (in_cap(r, t) && !append_intersection(xs, t, cy))
		return (false);
	return (true);
}

static bool	intersect_walls(t_object *cy, const t_ray *r,	t_intersections *xs)
{
	double	a;
  double b;
  double c;
  double disc;
  double t[2];

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
	if (r->origin.y + t[0] * r->direction.y > 0.0
		&& r->origin.y + t[0] * r->direction.y < cy->height
		&& !append_intersection(xs, t[0], cy))
		return (false);
	if (r->origin.y + t[1] * r->direction.y > 0.0
		&& r->origin.y + t[1] * r->direction.y < cy->height
		&& !append_intersection(xs, t[1], cy))
		return (false);
	return (true);
}

bool	cylinder_intersect(t_object *cy, const t_ray *r, t_intersections *xs)
{
	if (!intersect_walls(cy, r, xs))
		return (false);
	return (intersect_caps(cy, r, xs));
}

static bool	append_cone_hit(t_object *cn, const t_ray *r,	t_intersections *xs, double t)
{
	double	y;

	y = r->origin.y + t * r->direction.y;
	if (y <= -cn->height || y >= 0.0)
		return (true);
	return (append_intersection(xs, t, cn));
}

static bool	intersect_cone_walls(t_object *cn, const t_ray *r, t_intersections *xs)
{
	double	a;
	double	b;
	double	c;
	double	disc;
	double	t[2];

	a = powl(r->direction.x, 2)	+ powl(r->direction.z, 2)	- powl(r->direction.y, 2);
	b = 2.0 * (r->origin.x * r->direction.x	+ r->origin.z * r->direction.z - r->origin.y * r->direction.y);
	c = powl(r->origin.x, 2) + powl(r->origin.z, 2)	- powl(r->origin.y, 2);
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

static bool	intersect_cone_caps(t_object *cn, const t_ray *r, t_intersections *xs)
{
	double	t;
	double	x;
	double	z;

	if (fabs(r->direction.y) < EPSILON)
		return (true);              /* parallel to the cap */
	t = (-cn->height - r->origin.y) / r->direction.y;
	x = r->origin.x + t * r->direction.x;
	z = r->origin.z + t * r->direction.z;
	if (x * x + z * z <= cn->height * cn->height
		&& !append_intersection(xs, t, cn))
		return (false);
	return (true);
}

bool	cone_intersect(t_object *cn, const t_ray *r, t_intersections *xs)
{
	if (!intersect_cone_walls(cn, r, xs))
		return (false);
	return (intersect_cone_caps(cn, r, xs));
}
