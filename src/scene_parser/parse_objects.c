/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 13:15:04 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/08 13:15:07 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

const char	*parse_sphere(t_context *c, char **tok, int n)
{
	t_object	*o;
	double		diameter;

	if (n != 4)
		return ("sphere: expected 'sp x,y,z diameter r,g,b'");
	o = &c->scene->objects[c->obj_i];
	o->type = OBJ_SPHERE;
	if (!parse_point(tok[1], &o->pos))
		return ("sphere: center must be x,y,z");
	if (!parse_double(tok[2], &diameter) || diameter <= 0.0)
		return ("sphere: diameter must be a number > 0");
	o->radius = diameter / 2.0;
	if (!parse_color(tok[3], &o->color))
		return ("sphere: color must be r,g,b integers in [0, 255]");
	c->obj_i++;
	return (NULL);
}

const char	*parse_plane(t_context *c, char **tok, int n)
{
	t_object	*o;

	if (n != 4)
		return ("plane: expected 'pl x,y,z nx,ny,nz r,g,b'");
	o = &c->scene->objects[c->obj_i];
	o->type = OBJ_PLANE;
	if (!parse_point(tok[1], &o->pos))
		return ("plane: point must be x,y,z");
	if (!parse_unit_vec(tok[2], &o->axis))
		return ("plane: normal must be a unit vector x,y,z");
	if (!parse_color(tok[3], &o->color))
		return ("plane: color must be r,g,b integers in [0, 255]");
	c->obj_i++;
	return (NULL);
}

const char	*parse_cylinder(t_context *c, char **tok, int n)
{
	t_object	*o;
	double		diameter;

	if (n != 6)
		return ("cylinder: expected 'cy x,y,z ax,ay,az diam height r,g,b'");
	o = &c->scene->objects[c->obj_i];
	o->type = OBJ_CYLINDER;
	if (!parse_point(tok[1], &o->pos))
		return ("cylinder: center must be x,y,z");
	if (!parse_unit_vec(tok[2], &o->axis))
		return ("cylinder: axis must be a unit vector x,y,z");
	if (!parse_double(tok[3], &diameter) || diameter <= 0.0)
		return ("cylinder: diameter must be a number > 0");
	if (!parse_double(tok[4], &o->height) || o->height <= 0.0)
		return ("cylinder: height must be a number > 0");
	if (!parse_color(tok[5], &o->color))
		return ("cylinder: color must be r,g,b integers in [0, 255]");
	o->radius = diameter / 2.0;
	c->obj_i++;
	return (NULL);
}
