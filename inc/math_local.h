/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_local.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 10:41:23 by sdarius-          #+#    #+#             */
/*   Updated: 2026/09/30 11:06:07 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_LOCAL_H
#define MATH_LOCAL_H

#include <math.h>
#include <stdbool.h>

#define EPSILON 1e-5

/*Checks if two double variables are equal under a Epsilon*/
bool	d_equality(double a, double b);


#endif
