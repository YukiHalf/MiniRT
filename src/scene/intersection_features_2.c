/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_features_2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 13:20:47 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/07 12:24:45 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_intersection	*hit(t_intersections *xs)
{
	size_t			i;
	t_intersection	*lowest;

	i = 0;
	lowest = NULL;
	while (i < xs->count)
	{
		if (xs->items[i].t >= 0.0 && (lowest == NULL
				|| xs->items[i].t < lowest->t))
			lowest = &xs->items[i];
		i++;
	}
	return (lowest);
}
