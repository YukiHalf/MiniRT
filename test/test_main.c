/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 13:20:01 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/07 11:51:30 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "matrix.h"
#include "mlx_f.h"
#include "scene.h"
#include "tuple.h"
#include <scene.h>
#include <stdio.h>
#include <stdlib.h>

void	DEBUG_print_matrice(size_t size, double m[static size][size])
{
	for (int i = 0; i < size; i++)
	{
		for (int k = 0; k < size; k++)
		{
			printf("%f ", m[i][k]);
		}
		printf("\n");
	}
	printf("\n");
}

void	DEBUG_print_tuple(t_tuple tup)
{
	printf("%f %f %f %f\n", tup.x, tup.y, tup.z, tup.w);
}

void	draw_point(t_scene *scene, t_tuple point, t_rgb c)
{
	double	x;
	double	y;

	x = round(scene->image->height / 2 + point.x * 100);
	y = round(scene->image->width / 2 - point.z * 100);
	if (x < 0 || x >= scene->image->width)
		return ;
	if (y < 0 || y >= scene->image->height)
		return ;
	write_pixel_mlx(scene->image, c, (uint32_t)x, (uint32_t)y);
}

void	fill_circle(t_scene *scene, t_tuple point, t_rgb c)
{
	double	x;
	double	y;

	x = round(scene->image->height / 2 + point.x * 100);
	y = round(scene->image->width / 2 - point.z * 100);
	if (x < 0 || x >= scene->image->width)
		return ;
	if (y < 0 || y >= scene->image->height)
		return ;
	for (int i = 0; i < y; i++)
		write_pixel_mlx(scene->image, c, (uint32_t)x, (uint32_t)y);
}

void	render_world(t_scene *scene, t_intersections *xs, t_object *obj,
		t_ray *ray)
{
	double	wall_size;
	double	pixel_size;
	double	half;
	double	wall_z;
	t_tuple	ray_origin;
	t_tuple	position;

	wall_size = 10.0;
	pixel_size = wall_size / scene->image->width;
	half = 5.0;
	double world_y, world_x;
	wall_z = 10;
	ray_origin = init_point(0, 0, -5);
	for (int y = 0; y < scene->image->height; y++)
	{
		world_y = half - pixel_size * y;
		for (int x = 0; x < scene->image->width; x++)
		{
			world_x = -half + pixel_size * x;
			position = init_point(world_x, world_y, wall_z);
			*ray = init_ray(ray_origin, norm_tup(subst_tup(position,
							ray_origin)));
			xs->count = 0;
			collect_sphere_intersections(xs, obj, ray);
			if (hit(xs) >= 0)
				write_pixel_mlx(scene->image, obj->color, x, y);
		}
	}
}

int	main(int argc, char **argv)
{
	t_scene			scene;
	t_intersections	xs;
	t_object		s;
	t_ray			r;
	t_tuple			pos;
	t_material		m;
	t_tuple			eyev;
	t_tuple			normalv;
	t_light			l;
	t_rgb res;
	if (!init_intersections(&xs))
		return (-1);
	s = init_sphere_default();
	set_transform(&s, init_translation(0, 1, 0));
	// init_mlx(&scene);
	// render_world(&scene,&xs,&s,&r);
	pos = init_point(0, 0, 0);
	m = material();
	eyev = init_vector(0, 0,-1);
	normalv = init_vector(0, 0, -1);
	l = point_light(init_point(0, 0, 10), (t_rgb){1, 1, 1});
	res = lighting((t_lighting_parms){.m = m, .l = l, .pos = pos, .eyev = eyev,.normalv = normalv});
	printf("%f %f %f ",res.r,res.b,res.g);
	// mlx_loop(scene.mlx);
	// mlx_terminate(scene.mlx);
	return (0);
}
