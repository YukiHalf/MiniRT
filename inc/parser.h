#ifndef PARSER_H
# define PARSER_H

# include <stddef.h>
# include <stdbool.h>
# include "libft/libft.h"

// Not sure what you are currently using, so i just added them and we can change them tomorrow when we meet :)
typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;
 
typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}	t_color;


/*
* Everything a ray can hit is a t_object. Fields used per type:
** sphere:   pos = center,        radius
** plane:    pos = point on it,   axis = normal
** cylinder: pos = center,        axis, radius, height
** (for bonus we add a shape that would use the same four fields)
*/
typedef enum e_obj_type
{
	OBJ_PLANE,
	OBJ_SPHERE,
	OBJ_CYLINDER
}	t_obj_type;
 
typedef struct s_object
{
	t_obj_type	type;
	t_vec3		pos;
	t_vec3		axis;
	double		radius;
	double		height;
	t_color		color;
}	t_object;

typedef struct s_ambient
{
	double	ratio;
	t_color	color;
}	t_ambient;
 
typedef struct s_camera
{
	t_vec3	pos;
	t_vec3	dir;
	double	fov;
}	t_camera;
 
typedef struct s_light
{
	t_vec3	pos;
	double	brightness;
	t_color	color;
}	t_light;

typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		*lights;
	int			light_count;
	t_object	*objects;
	int			object_count;
	bool		has_ambient;
	bool		has_camera;
	int			err_line;
}	t_scene;

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
}	t_line_type;

// file_reader.c
char	*read_file(const char *path);


#endif