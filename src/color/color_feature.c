/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_feature.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 14:14:11 by sdarius-          #+#    #+#             */
/*   Updated: 2026/09/28 14:26:16 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

t_rgb	init_rgb(double r, double b, double g)
{
	return ((t_rgb){r, g, b});
}

t_rgb	add_rgb(t_rgb c1, t_rgb c2)
{
	return ((t_rgb){c1.r + c2.r, c1.b + c2.b, c1.g + c2.g});
}

t_rgb	sub_rgb(t_rgb c1, t_rgb c2)
{
	return ((t_rgb){c1.r - c2.r, c1.b - c2.b, c1.g - c2.g});
}

t_rgb	mult_scalar_rgb(t_rgb c, double scalar)
{
	return ((t_rgb){c.r * scalar, c.b * scalar, c.g * scalar});
}

t_rgb	mult_color_rgb(t_rgb c1, t_rgb c2)
{
	return ((t_rgb){c1.r * c2.r, c1.b * c2.b, c1.g * c2.g});
}
