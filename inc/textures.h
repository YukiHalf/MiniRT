/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 11:17:56 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/08 12:27:25 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_H
#define TEXTURES_H
#include <math.h>
#include "tuple.h"
#include "color.h"
#include "matrix.h"
#include <stdbool.h>

#define BLACK (t_rgb){0,0,0}
#define WHITE (t_rgb){1,1,1}

/*Declare the scene.h object tag at file scope before using it in prototypes.*/
struct s_object;

typedef struct s_pattern
{
	t_rgb a;
	t_rgb b;
	bool has_pattern;
	t_mat4 transform;
}	t_pattern;

/*returns a pattern with color a and b*/
t_pattern stripe_pattern(t_rgb a,t_rgb b);
/*returns the color at a given point*/
t_rgb	stripe_at(t_pattern p, t_tuple point);
/*returns the color from the pattern at a given postions on object*/
t_rgb   stripe_at_object(t_pattern p,
         const struct s_object *object, t_tuple world_point);
/*sets a transfrom matrice for the pattern*/
void 	set_pattern_transform(t_pattern *p, t_mat4 t);
#endif
