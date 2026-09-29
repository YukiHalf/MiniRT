/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_f.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 11:47:30 by sdarius-          #+#    #+#             */
/*   Updated: 2026/09/29 12:04:10 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_F_H
#define MLX_F_H

#include "MLX42.h"
/*Start up all the prosess needed for mlx, and has some error checks. prints errors and returns -1. Returns 1 on success*/
int 	inti_mlx(mlx_t *mlx, mlx_image_t* image);
void 	write_pixel_mlx(mlx_image_t *image,t_rgb rgb,uint32_t x,uint32_t y);

#endif
