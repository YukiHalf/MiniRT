/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_features.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 13:20:30 by sdarius-          #+#    #+#             */
/*   Updated: 2026/09/28 13:20:57 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_lib.h"

bool	f_equality(float a, float b, float epsilon)
{
	float	sum;

	sum = a - b;
	return (fabs(sum) < epsilon);
}
