#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>
# include <stddef.h>
# include "color.h"
# include "libft.h"
# include "tuple.h"
# include "scene.h"
# include "math_local.h"

# define MAX_LIGHTS 1
# define MAX_TOKENS 8

typedef struct s_context
{
	t_rt_scene	*scene;
	int		obj_i;
	int		light_i;
}	t_context;

typedef const char	*(*t_line_fn)(void *ctx, char *line);

// file_read.c
const char	*read_scene_file(const char *path, t_line_fn fn, void *ctx, int *ln);

// number_util.c
int	parse_double(const char *s, double *out);
int	parse_range(const char *s, double lo, double hi, double *out);
int	parse_byte(const char *s, int *out);

// parse_objects.c
const char	*parse_sphere(t_context *c, char **tok, int n);
const char	*parse_plane(t_context *c, char **tok, int n);
const char	*parse_cylinder(t_context *c, char **tok, int n);
const char  *parse_cube(t_context *c, char **tok, int n);
const char  *parse_cone(t_context *c, char **tok, int n);

// parse_room.c
const char	*parse_ambient(t_context *c, char **tok, int n);
const char	*parse_camera(t_context *c, char **tok, int n);
const char	*parse_light(t_context *c, char **tok, int n);

// parse_util.c
bool			is_blank(char c);
int	tokenize(char *s, char **tok, int max);

// parse_vec.c
int	parse_point(char *s, t_tuple *out);
int	parse_color(char *s, t_rgb *out);
int	parse_unit_vec(char *s, t_tuple *out);

// scene_checker.c
t_line_type	classify(const char *token, size_t len);
bool		is_object(t_line_type type);
const char	*count_line(void *ctx, char *line);

// scene_parser.c
const char	*scene_load(t_rt_scene *scene, const char *path);
void			scene_free(t_rt_scene *scene);

// scene_parser2.c
const char	*parse_line(void *ctx, char *line);


#endif
