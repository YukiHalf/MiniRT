/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_features.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 11:19:13 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/02 11:40:20 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "scene.h"

t_object init_sphere_default()
{
	return((t_object){OBJ_SPHERE,init_point(0,0,0),init_point(0,0,0),1,1,(t_rgb){1,1,1}});
}
