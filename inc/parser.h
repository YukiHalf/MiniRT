#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>
# include <stddef.h>
# include "color.h"
# include "libft.h"
# include "tuple.h"

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

char			*read_file(const char *path);
bool			is_blank(char c);
const char	*count_elements(t_rt_scene *scene, char *buf);
const char	*scene_load(t_rt_scene *scene, const char *path);
void			scene_free(t_rt_scene *scene);

#endif
