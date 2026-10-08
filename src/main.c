/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 13:19:07 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/08 13:19:09 by sdarius-         ###   ########.fr       */
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

/*the parser stores center, radius and color in the object fields; chapter 7
works with unit spheres that carry a transform and a material instead, so
move the parsed values over*/
static void	prepare_parsed_scene(t_rt_scene *scene)
{
	t_object	*o;
	t_mat4		move;
	t_mat4		scale;
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
		if (o->type == OBJ_SPHERE)
		{
			move = init_translation(o->pos.x, o->pos.y, o->pos.z);
			scale = init_scaling(o->radius, o->radius, o->radius);
			set_transform(o, multy_m4(move.m, scale.m));
			o->pos = init_point(0, 0, 0);
			o->radius = 1.0;
		}
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
		{
			print_scene_error(&app.scene, error);
			return (1);
		}
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
