/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns_features.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 11:14:58 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/08 13:17:45 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "textures.h"

t_pattern	stripe_pattern(t_rgb a, t_rgb b)
{
	return ((t_pattern){.a = a, .b = b, .has_pattern = true,
		.transform = init_identy_m4()});
}

t_rgb	stripe_at(t_pattern p, t_tuple point)
{
	if ((int)floor(point.x) % 2 == 0)
		return (p.a);
	return (p.b);
}

t_rgb	stripe_at_object(t_pattern p, const t_object *obj, t_tuple pos)
{
	t_tuple	object_point;
	t_tuple	pattern_point;

	object_point = multy_m4_tup(inverse_m4(obj->transform.m).m, pos);
	pattern_point = multy_m4_tup(inverse_m4(p.transform.m).m, object_point);
	return (stripe_at(p, pattern_point));
}

void	set_pattern_transform(t_pattern *p, t_mat4 t)
{
	p->transform = t;
}
