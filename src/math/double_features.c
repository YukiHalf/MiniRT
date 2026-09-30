/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_features.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 13:20:30 by sdarius-          #+#    #+#             */
/*   Updated: 2026/09/30 10:47:37 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_local.h"

bool	d_equality(double a, double b)
{
	return (fabs(a - b) < EPSILON);
}
