/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 13:16:09 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/09 10:27:28 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static const char	*alloc_arrays(t_rt_scene *scene)
{
	if (scene->object_count > 0)
		scene->objects = ft_calloc(scene->object_count, sizeof(t_object));
	if (scene->light_count > 0)
		scene->lights = ft_calloc(scene->light_count, sizeof(t_light));
	if ((scene->object_count > 0 && !scene->objects) || (scene->light_count > 0
			&& !scene->lights))
		return ("memory allocation failed");
	return (NULL);
}

void	scene_free(t_rt_scene *scene)
{
	if (!scene)
		return ;
	free(scene->objects);
	free(scene->lights);
	scene->objects = NULL;
	scene->lights = NULL;
	scene->object_count = 0;
	scene->light_count = 0;
	scene->has_ambient = false;
	scene->has_camera = false;
}

const char	*scene_load(t_rt_scene *scene, const char *path)
{
	t_context	ctx;
	const char	*error;
	int			ln;

	if (!scene)
		return ("invalid scene");
	scene->err_line = 0;
	ln = 0;
	error = read_scene_file(path, count_line, scene, &ln);
	if (!error)
		error = alloc_arrays(scene);
	if (error)
	{
		scene->err_line = ln;
		scene_free(scene);
		return (error);
	}
	ctx.scene = scene;
	ctx.obj_i = 0;
	ctx.light_i = 0;
	error = read_scene_file(path, parse_line, &ctx, &ln);
	if (error)
		return (scene->err_line = ln, scene_free(scene), error);
	return (error);
}
