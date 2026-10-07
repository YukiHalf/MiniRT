/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_features.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 11:19:13 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/07 11:42:31 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_object	init_sphere_default(void)
{
	return ((t_object){.type = OBJ_SPHERE, .pos = init_point(0, 0, 0),
		.radius = 1.0, .color = {1.0, 1.0, 1.0},
		.transform = init_identy_m4(),.material = material()});
}

void	set_transform(t_object *obj, t_mat4 t)
{
	obj->transform = t;
}

t_tuple	normal_at(t_object obj, t_tuple p)
{
	t_tuple	obj_point;
	t_tuple	obj_normal;
	t_tuple	world_normal;

	obj_point = multy_m4_tup(inverse_m4(obj.transform.m).m, p);
	obj_normal = subst_tup(obj_point, init_point(0, 0, 0));
	world_normal = multy_m4_tup(transpose_m4(inverse_m4(obj.transform.m).m).m,
			obj_normal);
	world_normal.w = 0;
	return (norm_tup(world_normal));
}

t_tuple	reflect(t_tuple in, t_tuple normal)
{
	return (subst_tup(in, multy_tup_return(normal, 2 * dot_tup(in, normal))));
}

t_light 	point_light(t_tuple p,t_rgb i)
{
	return((t_light){.pos = p, .intensity = i});
}
