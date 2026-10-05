/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_features_2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 13:20:47 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/05 13:46:16 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

double	hit(t_intersections *xs)
{
	size_t	i;
	double	lowest;

	i = 0;
	lowest = -1.0;
	while (i < xs->count)
	{
		if (xs->items[i].t >= 0.0 && (lowest < 0.0 || xs->items[i].t < lowest))
			lowest = xs->items[i].t;
		i++;
	}
	return (lowest);
}
