/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 13:20:01 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/05 13:40:05 by sdarius-         ###   ########.fr       */
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

void	make_circle(t_scene *scene, t_rgb color)
{
	t_mat4	r;
	t_tuple	p;
	int		i;

	r = rotation_y(1);
	p = init_point(0, 0, 1);
	i = 0;
	while (i < 36000)
	{
		DEBUG_print_tuple(p);
		printf("\n");
		draw_point(scene, p, color);
		fill_circle(scene, p, color);
		p = multy_m4_tup(r.m, p);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_ray			r;
	t_object		s;
	t_intersections	xs;

	r = init_ray(init_point(0, 0, -3), init_vector(0, 0, 1));
	s = init_sphere_default();
	init_intersections(&xs);
	collect_sphere_intersections(&xs,&s,&r);
	double hitman = hit(&xs);

	printf("%d %6.0f %6.0f h:%6.0f| \n %p %p %p\n", xs.count, xs.items[0].t, xs.items[1].t, hitman,
		(void *)xs.items[0].t_object,(void *)xs.items[1].t_object,(void *)&s);
	return (0);
}
