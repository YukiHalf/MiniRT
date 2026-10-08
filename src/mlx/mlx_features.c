/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_features.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 11:48:02 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/08 13:13:04 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "libft.h"
#include "mlx_f.h"
#include "scene.h"

int	init_mlx(t_scene *scene)
{
	if (!scene)
		display_error("Malloc failed for scene", 1);
	scene->mlx = mlx_init(WIN_W, WIN_H, "miniRT", false);
	if (!scene->mlx)
	{
		ft_putendl_fd(mlx_strerror(mlx_errno), STDERR_FILENO);
		return (-1);
	}
	scene->image = mlx_new_image(scene->mlx, WIN_W, WIN_H);
	if (!scene->image)
	{
		mlx_close_window(scene->mlx);
		ft_putendl_fd(mlx_strerror(mlx_errno), STDERR_FILENO);
		return (-1);
	}
	if (mlx_image_to_window(scene->mlx, scene->image, 0, 0) == -1)
	{
		mlx_close_window(scene->mlx);
		ft_putendl_fd(mlx_strerror(mlx_errno), STDERR_FILENO);
		return (-1);
	}
	return (1);
}

static uint32_t	double_to_uint32(double value)
{
	if (value < 0.0)
		value = 0.0;
	else if (value > 1.0)
		value = 1.0;
	return ((uint32_t)(value * 255 + 0.5));
}

static uint32_t	convert_trgb_to_uint32(t_rgb rgb)
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;

	r = double_to_uint32(rgb.r);
	g = double_to_uint32(rgb.g);
	b = double_to_uint32(rgb.b);
	return ((r << 24) | (g << 16) | (b << 8) | 255u);
}

void	write_pixel_mlx(mlx_image_t *image, t_rgb rgb, uint32_t x, uint32_t y)
{
	uint32_t	color;

	color = convert_trgb_to_uint32(rgb);
	mlx_put_pixel(image, x, y, color);
}
