/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 13:15:49 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/08 13:15:51 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <math.h>

static int	split_commas(char *s, char **f)
{
	int	i;

	f[0] = s;
	i = 1;
	while (*s)
	{
		if (*s == ',')
		{
			if (i == 3)
				return (0);
			*s = '\0';
			f[i] = s + 1;
			i++;
		}
		s++;
	}
	return (i == 3);
}

int	parse_point(char *s, t_tuple *out)
{
	char	*f[3];

	if (!split_commas(s, f))
		return (0);
	out->w = 1;
	return (parse_double(f[0], &out->x) && parse_double(f[1], &out->y)
		&& parse_double(f[2], &out->z));
}

int	parse_color(char *s, t_rgb *out)
{
	char	*f[3];
	int		v[3];

	if (!split_commas(s, f))
		return (0);
	if (!parse_byte(f[0], &v[0]) || !parse_byte(f[1], &v[1])
		|| !parse_byte(f[2], &v[2]))
		return (0);
	out->r = v[0] / 255.0;
	out->g = v[1] / 255.0;
	out->b = v[2] / 255.0;
	return (1);
}

int	parse_unit_vec(char *s, t_tuple *out)
{
	double	len;

	if (!parse_point(s, out))
		return (0);
	len = sqrt(out->x * out->x + out->y * out->y + out->z * out->z);
	if (fabs(len - 1.0) > EPSILON)
		return (0);
	out->x /= len;
	out->y /= len;
	out->z /= len;
	out->w = 0;
	return (1);
}
