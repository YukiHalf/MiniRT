/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 12:13:28 by sdarius-          #+#    #+#             */
/*   Updated: 2026/09/30 11:50:47 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>
#include <sys/types.h>
#include "math_local.h"
#include "tuple.h"

typedef struct s_mat2
{
	double m[2][2];
}	t_mat2;

typedef struct s_mat3
{
	double m[3][3];
} t_mat3;

typedef struct s_mat4
{
	double m[4][4];
} t_mat4;
/*creates a 4x4 matrice from an given array. It returns it as a value*/
t_mat4	init_m4(const double a[static 4][4]);
/*creates a 3x3 matrice from an given array. It returns it as a value*/
t_mat3	init_m3(const double a[static 3][3]);
/*creates a 2x2 matrice from an given array. It returns it as a value*/
t_mat2	init_m2(const double a[static 2][2]);
/*checks if two same size matrix are equal.*/
bool	is_matrix_equal(size_t size, const double a[size][size],const double b[size][size]);
/*multiplies two 4x4 matrices, then returns the result as a value*/
t_mat4	multy_m4(const double a[static 4][4], const double b[static 4][4]);
/*multiplies a tup with a marice, then returns the result as a t_tuple value*/
t_tuple	multy_m4_tup(const double m[static 4][4], const t_tuple t);
#endif
