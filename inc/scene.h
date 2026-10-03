/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 10:14:50 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/02 11:55:54 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H
# include "MLX42.h"
# include "tuple.h"
#include "color.h"



typedef struct scene_s
{
	mlx_t		*mlx;
	mlx_image_t	*image;
}				t_scene;

typedef struct s_ray
{
	t_tuple		origin;
	t_tuple		direction;
}				t_ray;

typedef struct s_intersection
{
   double      t;
   t_object   *object;
}   t_intersection;

typedef struct s_intersections
{
   t_intersection   *items;
   size_t         count;
   size_t         capacity;
}   t_intersections;


typedef enum e_obj_type
{
	OBJ_PLANE,
	OBJ_SPHERE,
	OBJ_CYLINDER
}t_obj_type;

typedef struct s_object
{
	t_obj_type	type;
	t_tuple		pos;
	t_tuple		axis;
	double		radius;
	double		height;
	t_rgb		color;
}t_object;

typedef struct s_ambient
{
	double	ratio;
	t_rgb	color;
}t_ambient;

typedef struct s_camera
{
	t_tuple	pos;
	t_tuple	dir;
	double	fov;
}t_camera;

typedef struct s_light
{
	t_tuple	pos;
	double	brightness;
	t_rgb	color;
}t_light;

typedef struct s_rt_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		*lights;
	int			light_count;
	t_object	*objects;
	int			object_count;
	bool			has_ambient;
	bool			has_camera;
	int			err_line;
}t_rt_scene;

typedef enum e_line_type
{
	T_BLANK,
	T_UNKNOWN,
	T_AMBIENT,
	T_CAMERA,
	T_LIGHT,
	T_SPHERE,
	T_PLANE,
	T_CYLINDER
}t_line_type;


/* give the point position of a ray moved in t time*/
t_tuple ray_position(t_ray ray, double t);
/*initiates a ray*/
t_ray	init_ray(t_tuple origin, t_tuple direction);
/*initiates the intersections struct*/
t_intersections init_intersections(void);

#endif
