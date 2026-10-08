/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 13:18:25 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/08 13:18:26 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

uint32_t	color_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return ((uint32_t)r << 24 | (uint32_t)g << 16 | (uint32_t)b << 8 | a);
}

static uint8_t	to_byte(double value)
{
	if (!(value > 0.0))
		return (0);
	if (value >= 1.0)
		return (255);
	return ((uint8_t)(value * 255.0 + 0.5));
}

uint32_t	color_from_unit(double r, double g, double b)
{
	return (color_rgba(to_byte(r), to_byte(g), to_byte(b), 255));
}

void	pixel_put(t_app *app, int x, int y, uint32_t color)
{
	if (x < 0 || y < 0 || x >= app->width || y >= app->height)
		return ;
	mlx_put_pixel(app->img, (uint32_t)x, (uint32_t)y, color);
}

void	image_fill(t_app *app, uint32_t color)
{
	int	x;
	int	y;

	y = 0;
	while (y < app->height)
	{
		x = 0;
		while (x < app->width)
		{
			pixel_put(app, x, y, color);
			x++;
		}
		y++;
	}
}
