/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 10:14:50 by sdarius-          #+#    #+#             */
/*   Updated: 2026/09/29 10:54:22 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
#define SCENE_H
#include "MLX42.h"

#define WIDTH 512
#define HEIGHT 512

typedef struct scene_s
{
	mlx_t* mlx;
	mlx_image_t* image;
}	t_scene;


#endif
