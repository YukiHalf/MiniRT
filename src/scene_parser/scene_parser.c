#include "../../inc/parser.h"

static const char	*alloc_arrays(t_scene *s)
{
	if (s->object_count > 0)
		s->objects = ft_calloc(s->object_count, sizeof(t_object));
	if (s->light_count > 0)
		s->lights = ft_calloc(s->light_count, sizeof(t_light));
	if ((s->object_count > 0 && !s->objects)
		|| (s->light_count > 0 && !s->lights))
		return ("memory allocation failed");
	return (NULL);
}

void	scene_free(t_scene *scene)
{
	free(scene->objects);
	free(scene->lights);
	scene->objects = NULL;
	scene->lights = NULL;
	scene->object_count = 0;
	scene->light_count = 0;
}

const char	*scene_load(t_scene *s, const char *path)
{
	char		*buf;
	const char	*err;
 
	buf = read_file(path);
	if (!buf)
		return ("cannot read the scene file");
	err = count_elements(s, buf);
	if (!err)
		err = alloc_arrays(s);
  // job's not finished
	if (err)
		scene_free(s);
	return (err);
}
