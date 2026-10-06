/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_features_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 12:22:56 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/06 12:31:47 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_material	material(void)
{
	return ((t_material){.color = (t_rgb){1, 1, 1}, .ambient = 0.1,
		.diffuse = 0.9, .specular = 0.9, .shininess = 200.0});
}
