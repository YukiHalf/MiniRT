/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 13:20:01 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/06 12:09:51 by sdarius-         ###   ########.fr       */
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

void render_world(t_scene *scene,t_intersections *xs,t_object *obj,t_ray *ray)
{
	double wall_size = 10.0;
	double pixel_size = wall_size / scene->image->width;
	double half = 5.0;
	double world_y,world_x;
	double wall_z = 10;
	t_tuple ray_origin = init_point(0,0,-5);
	for(int y = 0; y < scene->image->height;y++)
	{
		world_y = half - pixel_size * y;
		for(int x = 0;x < scene->image->width;x++)
		{
			world_x = -half + pixel_size * x;
			t_tuple position = init_point(world_x,world_y,wall_z);
			*ray = init_ray(ray_origin,norm_tup(subst_tup(position,ray_origin)));
			xs->count = 0;
			collect_sphere_intersections(xs,obj,ray);
			if(hit(xs) >= 0)
				write_pixel_mlx(scene->image,obj->color,x,y);
		}
	}
}


int	main(int argc, char **argv)
{
	t_scene scene;
	t_intersections xs;
	t_object s;
	t_ray r;

	if(!init_intersections(&xs))
		return -1;
	s = init_sphere_default();
	set_transform(&s,init_translation(0,1,0));
	//init_mlx(&scene);
	//render_world(&scene,&xs,&s,&r);
	t_tuple n = normal_at(s,init_point(0,1.70711,-0.70711));
	DEBUG_print_tuple(n);
	t_mat4 m = multy_m4(init_scaling(1,0.5,1).m,rotation_z(M_PI/5).m);
	set_transform(&s,m);
	n = normal_at(s,init_point(0,sqrt(2)/2,-(sqrt(2))/2));
	DEBUG_print_tuple(n);
	//mlx_loop(scene.mlx);
	//mlx_terminate(scene.mlx);

	return (0);
}
