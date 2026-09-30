#include "../../inc/parser.h"

static t_line_type	kind_of_line(const char *s)
{
	size_t	len;
 
	while (*s && *s != '\n' && is_blank(*s))
		s++;
	len = 0;
	while (s[len] && s[len] != '\n' && !is_blank(s[len]))
		len++;
	if (len == 0)
		return (T_BLANK);
	return (classify(s, len));
}
 
static t_line_type	classify(const char *p, size_t len)
{
	if (ft_strncmp(p, "A", 2))
		return (T_AMBIENT);
	if (ft_strncmp(p, "C", 2))
		return (T_CAMERA);
	if (ft_strncmp(p, "L", 2))
		return (T_LIGHT);
	if (ft_strncmp(p, "sp", 3))
		return (T_SPHERE);
	if (ft_strncmp(p, "pl", 3))
		return (T_PLANE);
	if (ft_strncmp(p, "cy", 3))
		return (T_CYLINDER);
	return (T_UNKNOWN);
}

static char	*next_line(char *s)
{
	while (*s && *s != '\n')
		s++;
	if (*s == '\n')
		s++;
	return (s);
}
 
const char	*count_elements(t_scene *s, char *buf)
{
	int		line;
	t_line_type	kind;
 
	line = 1;
	while (*buf)
	{
		kind = kind_of_line(buf);
		if (kind == T_UNKNOWN)
			return (scene_err(s, line, "unknown element identifier"));
		if (kind == T_LIGHT)
			s->light_count++;
		if (kind >= T_SPHERE)
			s->object_count++;
		buf = next_line(buf);
		line++;
	}
	return (NULL);
}
 