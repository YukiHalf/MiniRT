/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 11:17:56 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/08 11:48:25 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_H
#define TEXTURES_H
#include <math.h>
#include "tuple.h"
#include "color.h"
#include <stdbool.h>
#define BLACK (t_rgb){0,0,0}
#define WHITE (t_rgb){1,1,1}



typedef struct s_pattern
{
	t_rgb a;
	t_rgb b;
	bool has_pattern;
}	t_pattern;

/*returns a pattern with color a and b*/
t_pattern stripe_pattern(t_rgb a,t_rgb b);
/*returns the color at a given point*/
t_rgb	stripe_at(t_pattern p, t_tuple point);
#endif
