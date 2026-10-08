/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns_features.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 11:14:58 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/08 11:49:08 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textures.h"

t_pattern	stripe_pattern(t_rgb a, t_rgb b)
{
	return ((t_pattern){.a = a, .b = b,.has_pattern = true});
}
t_rgb	stripe_at(t_pattern p, t_tuple point)
{
	if ((int)floor(point.x) % 2 == 0)
		return (p.a);
	return(p.b);
}
