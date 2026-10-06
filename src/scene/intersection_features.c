/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_features.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 11:54:20 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/06 10:19:55 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	init_intersections(t_intersections *xs)
{
	xs->items = malloc(sizeof(*xs->items) * 8);
	if (!xs->items)
		return (false);
	xs->count = 0;
	xs->capacity = 8;
	return (true);
}

bool	sphere_intersect(t_object *s, t_ray r2, double *t0, double *t1)
{
	t_tuple	offset;
	double 	a;
	double	b;
	double	c;
	double	discriminant;
	t_ray r;

	r  = transform_ray(r2,inverse_m4(s->transform.m));
	offset = subst_tup(r.origin, s->pos);
	a =	dot_tup(r.direction, r.direction);
	b = 2.0 * dot_tup(r.direction, offset);
	c = dot_tup(offset, offset) - s->radius * s->radius;
	discriminant = b * b - 4.0 * dot_tup(r.direction, r.direction) * c;
	if (discriminant < 0)
		return (false);
	*t0 = (-b - sqrt(discriminant)) / (2.0 * a);
	*t1 = (-b + sqrt(discriminant)) / (2.0 * a);
	return (true);
}
bool	size_up_intersections_cap(t_intersections *xs)
{
	size_t			new_capacity;
	size_t			i;
	t_intersection	*new_i;

	if(xs->capacity > SIZE_MAX / sizeof(*xs->items) / 2)
		return (false);
	new_capacity = xs->capacity * 2;
	new_i = malloc(sizeof(*new_i) * new_capacity);
	if (!new_i)
		return (false);
	i = 0;
	while (i < xs->count)
	{
		new_i[i] = xs->items[i];
		i++;
	}
	free(xs->items);
	xs->items = new_i;
	xs->capacity = new_capacity;
	return (true);
}

bool	append_intersection(t_intersections *xs, double t, t_object *obj)
{
	if (xs->count == xs->capacity)
	{
		if (size_up_intersections_cap(xs) == false)
			return (false);
	}
	xs->items[xs->count].t = t;
	xs->items[xs->count].t_object = obj;
	xs->count++;
	return (true);
}

bool	collect_sphere_intersections(t_intersections *xs, t_object *sphere,
		const t_ray *ray)
{
	double	t0;
	double	t1;

	if (!sphere_intersect(sphere, *ray, &t0, &t1))
		return (true);
	if (!append_intersection(xs, t0, sphere))
		return (false);
	if (!append_intersection(xs, t1, sphere))
		return (false);
	return (true);
}
