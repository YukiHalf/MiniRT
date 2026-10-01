/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 12:13:28 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/01 13:32:05 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>
#include <sys/types.h>
#include "math_local.h"
#include "tuple.h"
#include "libft.h"

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

/*created this basicaly for just a function because it requires six parameters*/
typedef struct s_shear
{
	double xy;
	double xz;
	double yx;
	double yz;
	double zx;
	double zy;
}	t_shear;

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
/*create a indentity matrice and returns it by value*/
t_mat4	init_identy_m4(void);
/*returns basicaly the given matrix back, book says is important so well see*/
t_mat4	multy_m4_identy(const double m[static 4][4]);
/*transposes a 4x4 matrix, baisicaly the row becomes the col and so on kinda*/
t_mat4	transpose_m4(const double m[static 4][4]);
/*calculates the determinant of a 2x2 matrix*/
double	deter_m2(const double m[static 2][2]);
/*returns as a value the submatrix of size 2x2 from 3x3 by removing the specified row and col*/
t_mat2	submatrix_m3_t_m2(const double m[static 3][3], int row, int col);
/*returns as a value the submatrix of size 3x3 from 4x4 by removing the specified row and col*/
t_mat3	submatrix_m4_t_m3(const double m[static 4][4], int row, int col);
/*return the value of minor of a 3x3 matrice*/
double minor_m3(const double m[static 3][3],int row,int col);
/*returns the minor but if row + col odd then it negates the result*/
double cofractor_m3(const double m[static 3][3],int row,int col);
/*returns the determinant of a 3x3 matrice*/
double deter_m3(const double m[static 3][3]);
/*returns the determinant of a 4x4 matice*/
double	deter_m4(const double m[static 4][4]);
/*this i just copied m3 and changed the 2 to 3 so if is broken myea*/
double cofractor_m4(const double m[static 4][4],int row,int col);
/*still could be broken, bu i get good result*/
double	minor_m4(const double m[static 4][4], int row, int col);
/*checks if a m4 matrice is invertible*/
bool is_invertible_m4(const double m[static 4][4]);
/*inverts the marice m4*/
t_mat4	inverse_m4(const double m[static 4][4]);
/*returns by value a m4 translation*/
t_mat4	init_translation(double x, double y, double z);
/*returns by value a m4 scaling*/
t_mat4 init_scaling(double x,double y,double z);
/*returns by value a rotation matrice for x axis*/
t_mat4	rotation_x(double radians);
/*returns by value a rotaion matrice for y axis*/
t_mat4	rotation_y(double radians);
/*returns by value a rotation matrice for z axis*/
t_mat4	rotation_z(double radians);
/*returns by value a shearing matrice*/
t_mat4	init_shearing(t_shear amounts);
#endif
