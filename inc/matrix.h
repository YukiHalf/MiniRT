/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 12:13:28 by sdarius-          #+#    #+#             */
/*   Updated: 2026/09/30 10:14:07 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
#define MATRIX_H

typedef struct s_mat4
{
	double m[4][4];
} t_mat4;
/*creates a 4x4 matrice from an given array. It returns it as a value*/
t_mat4	init_m4(const double a[static 4][4]);


#endif
