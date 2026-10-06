#include "parser.h"

t_line_type	classify(const char *token, size_t len)
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

bool	is_object(t_line_type type)
{
	return (type == T_SPHERE || type == T_PLANE || type == T_CYLINDER);
}

const char	*count_line(void *ctx, char *line)
{
	t_rt_scene	*scene;
	char		*tok[MAX_TOKENS];
	t_line_type	type;
	int		n;

	scene = ctx;
	n = tokenize(line, tok, MAX_TOKENS);
	if (n < 0)
		return ("too many fields on this line");
	if (n == 0)
		return (NULL);
	type = classify(tok[0], ft_strlen(tok[0]));
	if (type == T_UNKNOWN)
		return ("unknown element identifier");
	if (type == T_LIGHT)
		scene->light_count++;
	else if (is_object(type))
		scene->object_count++;
	return (NULL);
}
