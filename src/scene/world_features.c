/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_features.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 13:09:43 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/07 13:18:08 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	is_shadowed(t_rt_scene w, t_tuple point)
{
	t_tuple			v;
	double			distance;
	t_tuple			direction;
	t_ray			r;
	t_intersections	xs;

	v = subst_tup(w.lights->pos, point);
	distance = magn_tup(v);
	direction = norm_tup(v);
	r = init_ray(point, direction);
	xs = intersect_world(w, r);
	if (hit(&xs) && hit(&xs)->t < distance)
		return (true);
	else
		return (false);
}
