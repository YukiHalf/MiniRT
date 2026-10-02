#include "parser.h"

static t_line_type	classify(const char *token, size_t len)
{
	if (len == 1 && token[0] == 'A')
		return (T_AMBIENT);
	if (len == 1 && token[0] == 'C')
		return (T_CAMERA);
	if (len == 1 && token[0] == 'L')
		return (T_LIGHT);
	if (len == 2 && token[0] == 's' && token[1] == 'p')
		return (T_SPHERE);
	if (len == 2 && token[0] == 'p' && token[1] == 'l')
		return (T_PLANE);
	if (len == 2 && token[0] == 'c' && token[1] == 'y')
		return (T_CYLINDER);
	return (T_UNKNOWN);
}

static const char	*scene_error(t_rt_scene *scene, int line,
	const char *message)
{
	scene->err_line = line;
	return (message);
}

static t_line_type	line_type(const char *line)
{
	size_t	len;

	while (*line && *line != '\n' && is_blank(*line))
		line++;
	len = 0;
	while (line[len] && line[len] != '\n' && !is_blank(line[len]))
		len++;
	if (len == 0)
		return (T_BLANK);
	return (classify(line, len));
}

static char	*next_line(char *line)
{
	while (*line && *line != '\n')
		line++;
	if (*line == '\n')
		line++;
	return (line);
}

const char	*count_elements(t_rt_scene *scene, char *buf)
{
	int			line_number;
	t_line_type	type;

	line_number = 1;
	while (*buf)
	{
		type = line_type(buf);
		if (type == T_UNKNOWN)
			return (scene_error(scene, line_number,
					"unknown element identifier"));
		if (type == T_AMBIENT)
			scene->has_ambient = true;
		else if (type == T_CAMERA)
			scene->has_camera = true;
		else if (type == T_LIGHT)
			scene->light_count++;
		else if (type >= T_SPHERE)
			scene->object_count++;
		buf = next_line(buf);
		line_number++;
	}
	return (NULL);
}
