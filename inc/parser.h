#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>
# include <stddef.h>
# include "color.h"
# include "libft.h"
# include "tuple.h"
#include "scene.h"

char			*read_file(const char *path);
bool			is_blank(char c);
const char	*count_elements(t_rt_scene *scene, char *buf);
const char	*scene_load(t_rt_scene *scene, const char *path);
void			scene_free(t_rt_scene *scene);

#endif
