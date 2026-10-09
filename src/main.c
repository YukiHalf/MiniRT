/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 13:19:07 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/09 10:19:56 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "minirt.h"
#include "parser.h"
#include "world.h"
#include <math.h>

static bool	has_rt_ext(const char *path)
{
	size_t	len;

	len = ft_strlen(path);
	return (len > 3 && ft_strncmp(path + len - 3, ".rt", 4) == 0);
}

static void	print_scene_error(const t_rt_scene *scene, const char *error)
{
	print_error(error);
	if (scene->err_line > 0)
	{
		ft_putstr_fd("on line: ", STDERR_FILENO);
		ft_putnbr_fd(scene->err_line, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
}

/*returns the rotation matrix that turns the canonical +y axis into axis*/
static t_mat4	axis_rotation(t_tuple axis)
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

/*the parser stores base point, size and color in the object fields; the book
works with canonical shapes in local space that carry a transform and a
material instead, so move the parsed values over per shape. Convention: a
cylinder or cone pos is the center of its base circle and height extends
along the axis from there, like the .rt subject describes it*/
static void	prepare_sphere(t_object *o)
{
	t_mat4	move;
	t_mat4	scale;

	move = init_translation(o->pos.x, o->pos.y, o->pos.z);
	scale = init_scaling(o->radius, o->radius, o->radius);
	set_transform(o, multy_m4(move.m, scale.m));
	o->pos = init_point(0, 0, 0);
	o->radius = 1.0;
}

static void	prepare_plane(t_object *o)
{
	t_mat4	move;
	t_mat4	spin;

	move = init_translation(o->pos.x, o->pos.y, o->pos.z);
	spin = axis_rotation(norm_tup(o->axis));
	set_transform(o, multy_m4(move.m, spin.m));
}

static void	prepare_cube(t_object *o)
{
	t_mat4	move;
	t_mat4	scale;

	move = init_translation(o->pos.x, o->pos.y, o->pos.z);
	scale = init_scaling(o->height / 2.0, o->height / 2.0, o->height / 2.0);
	set_transform(o, multy_m4(move.m, scale.m));
}

/*chapter 13 cylinder: radius 1 along +y; the height stays a field because
the caps are clamped in local space (y from 0 to height), never scaled*/
static void	prepare_cylinder(t_object *o)
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
static void	prepare_cone(t_object *o)
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

static void	prepare_object(t_object *o)
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

static void	prepare_parsed_scene(t_rt_scene *scene)
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
		{
			o->material.ambient = scene->ambient.ratio;
			o->material.color = mult_color_rgb(o->material.color,
					scene->ambient.color);
		}
		set_transform(o, init_identy_m4());
		prepare_object(o);
		i++;
	}
}

static void	world_setup(t_app *app)
{
	t_rt_scene	*scene;
	t_tuple		up;
	t_tuple		to;

	scene = &app->scene;
	camera_init(&app->camera, WIN_W, WIN_H, scene->camera.fov * M_PI / 180.0);
	up = init_vector(0, 1, 0);
	if (magn_tup(cross_arr(scene->camera.dir, up)) < EPSILON)
		up = init_vector(0, 0, 1);
	to = add_tup(scene->camera.pos, scene->camera.dir);
	app->view = view_transform(scene->camera.pos, to, up);
	app->camera.transform = app->view;
}

int	main(int argc, char **argv)
{
	t_app		app;
	const char	*error;

	if (argc > 2 || (argc == 2 && !has_rt_ext(argv[1])))
		return (print_error("Usage: ./miniRT [scene.rt]"));
	ft_bzero(&app, sizeof(app));
	if (argc == 2)
	{
		error = scene_load(&app.scene, argv[1]);
		if (error)
			return (print_scene_error(&app.scene, error), 1);
		prepare_parsed_scene(&app.scene);
	}
	world_setup(&app);
	error = app_init(&app);
	if (!error)
	{
		app_run(&app);
		error = app.error;
	}
	app_cleanup(&app);
	if (error)
		return (print_error(error));
	return (0);
}
