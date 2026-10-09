/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_features_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 12:22:56 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/09 12:06:29 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_material	material(void)
{
	return ((t_material){.color = (t_rgb){1, 1, 1}, .ambient = 0.1,
		.diffuse = 0.9, .specular = 0.9, .shininess = 200.0});
}

static t_rgb	util_ligthing(t_lighting_parms parm, t_rgb effective_color,
		double light_dot_normal)
{
	double	reflect_dot_eye;
	t_tuple	reflectv;
	t_rgb	diffuse;
	t_rgb	specular;
	t_tuple	lightv;

	lightv = norm_tup(subst_tup(parm.l.pos, parm.pos));
	diffuse = mult_scalar_rgb(effective_color, parm.m.diffuse
			* light_dot_normal);
	reflectv = reflect(nega_tup_return(lightv), parm.normalv);
	reflect_dot_eye = dot_tup(reflectv, parm.eyev);
	if (reflect_dot_eye <= 0)
		specular = (t_rgb){0, 0, 0};
	else
		specular = mult_scalar_rgb(parm.l.intensity, parm.m.specular
				* pow(reflect_dot_eye, parm.m.shininess));
	return (add_rgb(diffuse, specular));
}

t_rgb	lighting(t_lighting_parms parm)
{
	t_rgb	effective_color;
	t_rgb	ambient;
	double	light_dot_normal;
	t_rgb	diffuse;
	t_rgb	specular;

	effective_color = mult_color_rgb(parm.m.color, parm.l.intensity);
	ambient = mult_scalar_rgb(mult_color_rgb(parm.m.color, parm.ambient_color),
			parm.m.ambient);
	if (parm.in_shadow)
		return (ambient);
	light_dot_normal = dot_tup(norm_tup(subst_tup(parm.l.pos, parm.pos)),
			parm.normalv);
	if (light_dot_normal < 0)
	{
		diffuse = (t_rgb){0, 0, 0};
		specular = (t_rgb){0, 0, 0};
	}
	else
		return (add_rgb(ambient, util_ligthing(parm, effective_color,
					light_dot_normal)));
	return (add_rgb(ambient, add_rgb(diffuse, specular)));
}

t_object	init_plane(void)
{
	return ((t_object){.type = OBJ_PLANE, .material = material(),
		.pos = init_point(0, 0, 0), .transform = init_identy_m4()});
}
