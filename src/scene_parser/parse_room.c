#include "parser.h"

const char	*parse_ambient(t_context *c, char **tok, int n)
{
	t_ambient	*a;

	a = &c->scene->ambient;
	if (n != 3)
		return ("ambient: expected 'A ratio r,g,b'");
	if (c->scene->has_ambient)
		return ("ambient: 'A' can only be declared once");
	if (!parse_range(tok[1], 0.0, 1.0, &a->ratio))
		return ("ambient: ratio must be a number in [0.0, 1.0]");
	if (!parse_color(tok[2], &a->color))
		return ("ambient: color must be r,g,b integers in [0, 255]");
	c->scene->has_ambient = true;
	return (NULL);
}

const char	*parse_camera(t_context *c, char **tok, int n)
{
	t_camera	*cam;

	cam = &c->scene->camera;
	if (n != 4)
		return ("camera: expected 'C x,y,z nx,ny,nz fov'");
	if (c->scene->has_camera)
		return ("camera: 'C' can only be declared once");
	if (!parse_point(tok[1], &cam->pos))
		return ("camera: position must be x,y,z");
	if (!parse_unit_vec(tok[2], &cam->dir))
		return ("camera: orientation must be a unit vector x,y,z");
	if (!parse_double(tok[3], &cam->fov) || cam->fov <= 0.0
		|| cam->fov >= 180.0)
		return ("camera: fov must be a number in ]0, 180[");
	c->scene->has_camera = true;
	return (NULL);
}

const char	*parse_light(t_context *c, char **tok, int n)
{
	t_light	*l;

	if (n != 4)
		return ("light: expected 'L x,y,z brightness r,g,b'");
	if (c->light_i >= MAX_LIGHTS)
		return ("light: 'L' can only be declared once");
	l = &c->scene->lights[c->light_i];
	if (!parse_point(tok[1], &l->pos))
		return ("light: position must be x,y,z");
	if (!parse_range(tok[2], 0.0, 1.0, &l->brightness))
		return ("light: brightness must be a number in [0.0, 1.0]");
	if (!parse_color(tok[3], &l->color))
		return ("light: color must be r,g,b integers in [0, 255]");
	c->light_i++;
	return (NULL);
}
