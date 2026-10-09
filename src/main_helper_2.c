/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 10:31:10 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/09 12:08:09 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "minirt.h"
#include "parser.h"
#include "world.h"
#include <math.h>

/*returns the rotation matrix that turns the canonical +y axis into axis*/
t_mat4	axis_rotation(t_tuple axis)
{
	t_mat4	r;
	t_tuple	e0;
	t_tuple	e2;

	e0 = norm_tup(cross_arr(axis, init_vector(0, 1, 0)));
	if (fabs(axis.y) > 0.9)
		e0 = norm_tup(cross_arr(axis, init_vector(0, 0, 1)));
	e2 = cross_arr(e0, axis);
	r = init_identy_m4();
	r.m[0][0] = e0.x;
	r.m[1][0] = e0.y;
	r.m[2][0] = e0.z;
	r.m[0][1] = axis.x;
	r.m[1][1] = axis.y;
	r.m[2][1] = axis.z;
	r.m[0][2] = e2.x;
	r.m[1][2] = e2.y;
	r.m[2][2] = e2.z;
	return (r);
}

void	prepare_object(t_object *o)
{
	if (o->type == OBJ_SPHERE)
		prepare_sphere(o);
	else if (o->type == OBJ_PLANE)
		prepare_plane(o);
	else if (o->type == OBJ_CUBE)
		prepare_cube(o);
	else if (o->type == OBJ_CYLINDER)
		prepare_cylinder(o);
	else if (o->type == OBJ_CONE)
		prepare_cone(o);
}

void	prepare_parsed_scene(t_rt_scene *scene)
{
	t_object	*o;
	int			i;

	i = 0;
	while (i < scene->object_count)
	{
		o = &scene->objects[i];
		o->material = material();
		o->material.color = o->color;
		if (scene->has_ambient)
			o->material.ambient = scene->ambient.ratio;
		set_transform(o, init_identy_m4());
		prepare_object(o);
		i++;
	}
}
