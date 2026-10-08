/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 13:20:01 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/08 12:04:24 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "math_local.h"
#include "matrix.h"
#include "mlx_f.h"
#include "scene.h"
#include "textures.h"
#include "world.h"
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
	t_tuple	lighting_pos;
	t_rgb	ligthing_color;
	t_light	light;
	t_tuple	pos;
	t_rgb	c;
	obj->material.color = (t_rgb){1, 0.2, 1};
	lighting_pos = init_point(-10, 10, -10);
	ligthing_color = (t_rgb){1, 1, 1};
	light = point_light(lighting_pos, ligthing_color);
	wall_size = 10.0;
	pixel_size = wall_size / scene->image->width;
	half = 5.0;
	double world_y, world_x;
	wall_z = 5;
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
			if (!intersect(xs, obj, ray))
				return ;
			if (hit(xs) != NULL)
			{
				pos = ray_position(*ray, hit(xs)->t);
				c = lighting((t_lighting_parms){.m = hit(xs)->t_object->material,
						.obj = hit(xs)->t_object,
						.l = light, .pos = pos,
						.eyev = nega_tup_return(ray->direction),
						.normalv = normal_at(*hit(xs)->t_object, pos)});
				write_pixel_mlx(scene->image, c, x, y);
			}
			else
				write_pixel_mlx(scene->image, (t_rgb){0, 0, 0}, x, y);
		}
	}
}

void DEBUG_print_color(t_rgb c)
{
	printf("%f %f %f\n", c.r, c.g, c.b);
}

/*Run with make test. Checks print actual/expected RGB and return nonzero on
** failure. Ambient-only lighting cases isolate pattern coordinate selection.*/
static int	passed;
static int	failed;

static void	check_color(const char *name, t_rgb got, t_rgb want)
{
	bool	ok;

	ok = d_equality(got.r, want.r) && d_equality(got.g, want.g)
		&& d_equality(got.b, want.b);
	if (ok)
		passed++;
	else
		failed++;
	printf("%s %s\n", ok ? "PASS" : "FAIL", name);
	printf("  got RGB:  ");
	DEBUG_print_color(got);
	printf("  want RGB: ");
	DEBUG_print_color(want);
}

static void	test_stripe_coordinates(void)
{
	t_pattern	p;

	printf("\n--- Stripe coordinates ---\n");
	p = stripe_pattern(WHITE, BLACK);
	check_color("before x=1", stripe_at(p, init_point(0.999, 0, 0)),
		WHITE);
	check_color("at x=1", stripe_at(p, init_point(1, 0, 0)), BLACK);
	check_color("repeat at x=2", stripe_at(p, init_point(2, 0, 0)), WHITE);
	check_color("negative fraction x=-0.1",
		stripe_at(p, init_point(-0.1, 0, 0)), BLACK);
	check_color("past negative boundary x=-1.001",
		stripe_at(p, init_point(-1.001, 0, 0)), WHITE);
	check_color("y and z do not affect stripes",
		stripe_at(p, init_point(0.5, 5, -7)), WHITE);
}

static void	test_pattern_transforms(void)
{
	t_object	object;
	t_pattern	p;

	printf("\n--- Object and pattern transforms ---\n");
	object = init_sphere_default();
	p = stripe_pattern(WHITE, BLACK);
	set_transform(&object, init_scaling(2, 2, 2));
	check_color("object scale: world x=1.5 -> pattern x=0.75",
		stripe_at_object(p, &object, init_point(1.5, 0, 0)), WHITE);
	set_transform(&object, init_identy_m4());
	set_pattern_transform(&p, init_scaling(2, 2, 2));
	check_color("pattern scale: world x=1.5 -> pattern x=0.75",
		stripe_at_object(p, &object, init_point(1.5, 0, 0)), WHITE);
	set_transform(&object, init_scaling(2, 2, 2));
	set_pattern_transform(&p, init_translation(0.5, 0, 0));
	check_color("object scale then pattern translation: x=2.5 -> 0.75",
		stripe_at_object(p, &object, init_point(2.5, 0, 0)), WHITE);
}

static void	test_pattern_lighting(void)
{
	t_object			object;
	t_lighting_parms	parms;

	printf("\n--- Patterns through lighting ---\n");
	object = init_sphere_default();
	set_transform(&object, init_scaling(2, 2, 2));
	object.material.pattern = stripe_pattern(WHITE, BLACK);
	object.material.ambient = 1;
	object.material.diffuse = 0;
	object.material.specular = 0;
	parms = (t_lighting_parms){.m = object.material, .obj = &object,
		.l = point_light(init_point(0, 0, -10), WHITE),
		.pos = init_point(1.5, 0, 0), .eyev = init_vector(0, 0, -1),
		.normalv = init_vector(0, 0, -1), .in_shadow = false};
	check_color("scaled object selects white stripe", lighting(parms), WHITE);
	parms.pos = init_point(2.5, 0, 0);
	check_color("scaled object selects black stripe", lighting(parms), BLACK);
	parms.pos = init_point(1.5, 0, 0);
	parms.l.intensity = (t_rgb){0.5, 0.25, 0.75};
	check_color("pattern color multiplied by light intensity",
		lighting(parms), (t_rgb){0.5, 0.25, 0.75});
	parms.m.ambient = 0.2;
	parms.m.diffuse = 0.9;
	parms.m.specular = 0.9;
	parms.in_shadow = true;
	check_color("shadow keeps only the patterned ambient color",
		lighting(parms), (t_rgb){0.1, 0.05, 0.15});
	parms.in_shadow = false;
	parms.l.intensity = WHITE;
	parms.m.ambient = 1;
	parms.m.diffuse = 0;
	parms.m.specular = 0;
	parms.m.color = (t_rgb){0.2, 0.4, 0.6};
	parms.m.pattern = stripe_pattern(BLACK, BLACK);
	check_color("black pattern is still an enabled pattern",
		lighting(parms), BLACK);
	parms.m.pattern.has_pattern = false;
	check_color("disabled pattern uses material color",
		lighting(parms), (t_rgb){0.2, 0.4, 0.6});
}

static void	test_pattern_world_ray(void)
{
	t_object		object;
	t_light			light;
	t_rt_scene		world;
	t_intersections	xs;
	t_ray			ray;

	printf("\n--- Ray hit through shade_hit and lighting ---\n");
	object = init_sphere_default();
	set_transform(&object, init_scaling(2, 2, 2));
	object.material.pattern = stripe_pattern(WHITE, BLACK);
	object.material.color = (t_rgb){0.2, 0.4, 0.6};
	object.material.ambient = 1;
	object.material.diffuse = 0;
	object.material.specular = 0;
	light = point_light(init_point(0, 0, -10), WHITE);
	world = (t_rt_scene){.objects = &object, .object_count = 1,
		.lights = &light, .light_count = 1};
	ray = init_ray(init_point(1.5, 0, -5), init_vector(0, 0, 1));
	if (!init_intersections(&xs))
	{
		failed++;
		printf("FAIL could not allocate intersections for the world check\n");
		return ;
	}
	check_color("ray hits white stripe on scaled sphere",
		color_at(&world, &ray, &xs), WHITE);
	free(xs.items);
}

int	main(void)
{
	test_stripe_coordinates();
	test_pattern_transforms();
	test_pattern_lighting();
	test_pattern_world_ray();
	printf("\nPattern checks: %d passed, %d failed\n", passed, failed);
	return (failed != 0);
}
