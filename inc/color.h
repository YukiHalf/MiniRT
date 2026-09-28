/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 13:42:57 by sdarius-          #+#    #+#             */
/*   Updated: 2026/09/28 14:26:38 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
#define COLOR_H

typedef struct rgb_s
{
	double r;
	double g;
	double b;
}			t_rgb;

/*initializez a t_rgb  and returns it by value*/
t_rgb	init_rgb(double r, double b, double g);
/*adds two t_rgb structs and returns a new t_rgb value*/
t_rgb	add_rgb(t_rgb c1, t_rgb c2);
/*subtracts two t_rgb structs and returns a new t_rgb value */
t_rgb	sub_rgb(t_rgb c1, t_rgb c2);
/*multiplies a t_rgb struct by a scalar then retuns the value*/
t_rgb	mult_scalar_rgb(t_rgb c, double scalar);
/*mutiplies a t_rgb by another then returns the value*/
t_rgb	mult_color_rgb(t_rgb c1, t_rgb c2);
#endif
