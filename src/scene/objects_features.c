/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_features.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 11:19:13 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/05 11:33:23 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_object	init_sphere_default(void)
{
	return((t_object){
		.type = OBJ_SPHERE, .pos = init_point(0, 0, 0), .radius = 1.0,
			.color = {1.0, 1.0, 1.0}
		});
}
