/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_features.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 11:48:02 by sdarius-          #+#    #+#             */
/*   Updated: 2026/09/29 12:08:47 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_f.h"
#include "scene.h"
#include "libft.h"
#include "color.h"

int 	inti_mlx(mlx_t *mlx, mlx_image_t* image)
{
	mlx = mlx_init(WIDTH, HEIGHT,"miniRT",false);
	if(!mlx)
	{
		ft_putendl_fd(mlx_strerror(mlx_errno),STDERR_FILENO);
		return (-1);
	}
	image = mlx_new_image(mlx,128,128); // hard coded for the moment
	if(!image)
	{
		mlx_close_window(mlx);
		ft_putendl_fd(mlx_strerror(mlx_errno),STDERR_FILENO);
		return (-1);
	}
	if(mlx_image_to_window(mlx,image,0,0) == -1)
	{
		mlx_close_window(mlx);
		ft_putendl_fd(mlx_strerror(mlx_errno),STDERR_FILENO);
		return (-1);
	}
	return (1);
}

static int32_t convert_trgb_to_uint32(t_rgb rgb)
{
// TO do 
}


void 	write_pixel_mlx(mlx_image_t *image,t_rgb rgb,uint32_t x,uint32_t y)
{
	uint32_t color;

	color = convert_trgb_to_uint32(rgb);
	mlx_put_pixel(image,x,y);
}
