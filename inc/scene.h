/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 10:14:50 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/06 11:39:30 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H
# include "MLX42.h"
# include "color.h"
# include "math.h"
# include "matrix.h"
# include "tuple.h"
# include <stdint.h>
# include <stdlib.h>
typedef struct scene_s
{
	mlx_t			*mlx;
	mlx_image_t		*image;
}					t_scene;

typedef struct s_ray
{
	t_tuple			origin;
	t_tuple			direction;
}					t_ray;

typedef enum e_obj_type
{
	OBJ_PLANE,
	OBJ_SPHERE,
	OBJ_CYLINDER
}					t_obj_type;

typedef struct s_object
{
	t_obj_type		type;
	t_tuple			pos;
	t_tuple			axis;
	double			radius;
	double			height;
	t_rgb			color;
	t_mat4			transform;
}					t_object;

typedef struct s_ambient
{
	double			ratio;
	t_rgb			color;
}					t_ambient;

typedef struct s_camera
{
	t_tuple			pos;
	t_tuple			dir;
	double			fov;
}					t_camera;

typedef struct s_light
{
	t_tuple			pos;
	double			brightness;
	t_rgb			color;
}					t_light;

typedef struct s_rt_scene
{
	t_ambient		ambient;
	t_camera		camera;
	t_light			*lights;
	int				light_count;
	t_object		*objects;
	int				object_count;
	bool			has_ambient;
	bool			has_camera;
	int				err_line;
}					t_rt_scene;

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
}					t_line_type;

typedef struct s_intersection
{
	double			t;
	const t_object	*t_object;
}					t_intersection;

typedef struct s_intersections
{
	t_intersection	*items;
	size_t			count;
	size_t			capacity;
}					t_intersections;

/* give the point position of a ray moved in t time*/
t_tuple				ray_position(t_ray ray, double t);
/*initiates a ray*/
t_ray				init_ray(t_tuple origin, t_tuple direction);
/*initiates an array of hits*/
bool				init_intersections(t_intersections *xs);
/*creates a sphere object at default position 0 0 0*/
t_object			init_sphere_default(void);
/*appends a double t(hit) to the intersection list*/
bool				append_intersection(t_intersections *xs, double t,
						t_object *obj);
/*doubles the current capacity of current ray intersection list*/
bool				size_up_intersections_cap(t_intersections *xs);
/*calculates the intersections with a sphere*/
bool				sphere_intersect(t_object *s, t_ray r2, double *t0,
						double *t1);
/*colects the calculated intersections and checks and appneds them to the intersections list*/
bool				collect_sphere_intersections(t_intersections *xs,
						t_object *sphere, const t_ray *ray);
/*finds the lowest nonnegative intersection*/
double				hit(t_intersections *xs);
/*transforms a ray either on translation or scailing*/
t_ray				transform_ray(t_ray r, t_mat4 m);
/*sets transfrom for a object*/
void				set_transform(t_object *obj, t_mat4 t);
/*returns the normal for a shpere/obj*/
t_tuple 	normal_at(t_object obj,t_tuple p);
#endif
