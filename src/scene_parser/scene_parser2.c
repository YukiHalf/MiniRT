/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 13:17:14 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/08 13:17:16 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool	has_room(t_context *c, t_line_type kind)
{
	if (is_object(kind))
		return (c->obj_i < c->scene->object_count);
	if (kind == T_LIGHT)
		return (c->light_i < c->scene->light_count);
	return (true);
}

static const char	*dispatch(t_context *c, t_line_type kind, char **tok, int n)
{
	if (kind == T_AMBIENT)
		return (parse_ambient(c, tok, n));
	if (kind == T_CAMERA)
		return (parse_camera(c, tok, n));
	if (kind == T_LIGHT)
		return (parse_light(c, tok, n));
	if (kind == T_SPHERE)
		return (parse_sphere(c, tok, n));
	if (kind == T_PLANE)
		return (parse_plane(c, tok, n));
	if (kind == T_CYLINDER)
		return (parse_cylinder(c, tok, n));
	return ("unknown element identifier");
}

const char	*parse_line(void *ctx, char *line)
{
	t_context	*c;
	char		*tok[MAX_TOKENS];
	int			n;
	t_line_type	kind;

	c = ctx;
	n = tokenize(line, tok, MAX_TOKENS);
	if (n < 0)
		return ("too many fields on this line");
	if (n == 0)
		return (NULL);
	kind = classify(tok[0], ft_strlen(tok[0]));
	if (!has_room(c, kind))
		return ("scene file changed while reading");
	return (dispatch(c, kind, tok, n));
}
