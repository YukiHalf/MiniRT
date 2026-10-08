/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 10:14:50 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/08 11:48:08 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H
# include "MLX42.h"
# include "color.h"
# include "math.h"
# include "matrix.h"
# include "textures.h"
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

typedef struct s_material
{
	t_rgb			color;
	double			ambient;
	double			diffuse;
	double			specular;
	double			shininess;
	t_pattern 		pattern;
}					t_material;

typedef struct s_object
{
	t_obj_type		type;
	t_tuple			pos;
	t_tuple			axis;
	double			radius;
	double			height;
	t_rgb			color;
	t_mat4			transform;
	t_material		material;
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
	t_rgb			intensity;
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

typedef struct s_lighting_parms
{
	t_material		m;
	t_light			l;
	t_tuple			pos;
	t_tuple			eyev;
	t_tuple			normalv;
	bool 			in_shadow;
}					t_lighting_parms;

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
/*calculates sphere intersections from a local-space ray, without transforming it*/
bool				sphere_intersect(t_object *s, t_ray r, double *t0,
						double *t1);
/*appends sphere hits from a local-space ray; true also means no hits*/
bool				collect_sphere_intersections(t_intersections *xs,
						t_object *sphere, const t_ray *ray);
/*finds the lowest nonnegative intersection*/
t_intersection	*hit(t_intersections *xs);
/*transforms a ray either on translation or scailing*/
t_ray				transform_ray(t_ray r, t_mat4 m);
/*sets transfrom for a object*/
void				set_transform(t_object *obj, t_mat4 t);
/*returns the normal for a shpere/obj*/
t_tuple				normal_at(t_object obj, t_tuple p);
/*returns the reflect from an in and normal*/
t_tuple				reflect(t_tuple in, t_tuple normal);
/*returns a point and intensity as a t_light value*/
t_light				point_light(t_tuple p, t_rgb i);
/*returns default material as value*/
t_material			material(void);
/*returns the color for a matching eye lvl and material*/
t_rgb	lighting(t_lighting_parms parm);
/*create a plane object*/
t_object init_plane();
/*transforms a world-space ray once, then appends its intersections to xs*/
bool				intersect(t_intersections *xs, t_object *shape,
						const t_ray *ray);
/*appends local-space hits for spheres/planes; true includes misses.
** false means allocation failure or unsupported type. Initialize xs first;
** neither function clears xs. Stored object pointers must remain valid.*/
bool				local_intersect(t_intersections *xs, t_object *shape,
						const t_ray *local_ray);
/*gets the local for shape types*/
t_tuple local_normal_at(t_object shape,t_tuple local_point);
#endif
