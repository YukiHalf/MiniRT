/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_features.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 16:16:54 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/02 11:03:24 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_ray	init_ray(t_tuple origin, t_tuple direction)
{
	t_ray	r;

	r.origin = init_point(origin.x, origin.y, origin.z);
	r.direction = init_vector(direction.x, direction.y, direction.z);
	return (r);
}

t_tuple ray_position(t_ray ray, double t)
{
	return(add_tup(ray.origin,multy_tup_return(ray.direction,t)));
}
