/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_features_3.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 13:46:42 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/08 10:30:24 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	intersect(t_intersections *xs, t_object *shape, const t_ray *ray)
{
	t_ray	local_ray;

	local_ray = transform_ray(*ray, inverse_m4(shape->transform.m));
	return (local_intersect(xs, shape, &local_ray));
}
t_tuple local_normal_at(t_object shape,t_tuple local_point)
{
	if(shape.type == OBJ_SPHERE)
		return(subst_tup(local_point,shape.pos));
	if(shape.type == OBJ_PLANE)
		return(init_vector(0,1,0));
}
