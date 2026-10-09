/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 10:29:16 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/09 10:33:13 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "minirt.h"
#include "parser.h"
#include "world.h"
#include <math.h>

/*the parser stores base point, size and color in the object fields; the book
works with canonical shapes in local space that carry a transform and a
material instead, so move the parsed values over per shape. Convention: a
cylinder or cone pos is the center of its base circle and height extends
along the axis from there, like the .rt subject describes it*/
void	prepare_sphere(t_object *o)
{
	t_mat4	move;
	t_mat4	scale;

	move = init_translation(o->pos.x, o->pos.y, o->pos.z);
	scale = init_scaling(o->radius, o->radius, o->radius);
	set_transform(o, multy_m4(move.m, scale.m));
	o->pos = init_point(0, 0, 0);
	o->radius = 1.0;
}

void	prepare_plane(t_object *o)
{
	t_mat4	move;
	t_mat4	spin;

	move = init_translation(o->pos.x, o->pos.y, o->pos.z);
	spin = axis_rotation(norm_tup(o->axis));
	set_transform(o, multy_m4(move.m, spin.m));
}

void	prepare_cube(t_object *o)
{
	t_mat4	move;
	t_mat4	scale;

	move = init_translation(o->pos.x, o->pos.y, o->pos.z);
	scale = init_scaling(o->height / 2.0, o->height / 2.0, o->height / 2.0);
	set_transform(o, multy_m4(move.m, scale.m));
}

/*chapter 13 cylinder: radius 1 along +y; the height stays a field because
the caps are clamped in local space (y from 0 to height), never scaled*/
void	prepare_cylinder(t_object *o)
{
	t_mat4	move;
	t_mat4	spin;
	t_mat4	scale;

	spin = axis_rotation(norm_tup(o->axis));
	move = init_translation(o->pos.x, o->pos.y, o->pos.z);
	scale = init_scaling(o->radius, 1.0, o->radius);
	set_transform(o, multy_m4(move.m, multy_m4(spin.m, scale.m).m));
	o->pos = init_point(0, 0, 0);
	o->radius = 1.0;
}

/*chapter 13 cone: apex at the local origin opening toward -y with radius
|y|, so the translation must place the apex (pos + axis * height), not the
base; the base circle then sits at local y = -height and the xz scaling of
radius/height gives it the parsed radius at that height*/
void	prepare_cone(t_object *o)
{
	t_mat4	move;
	t_mat4	spin;
	t_mat4	scale;
	t_tuple	apex;

	spin = axis_rotation(norm_tup(o->axis));
	apex = add_tup(o->pos, multy_tup_return(norm_tup(o->axis), o->height));
	move = init_translation(apex.x, apex.y, apex.z);
	scale = init_scaling(o->radius / o->height, 1.0, o->radius / o->height);
	set_transform(o, multy_m4(move.m, multy_m4(spin.m, scale.m).m));
	o->pos = init_point(0, 0, 0);
	o->radius = 1.0;
}
