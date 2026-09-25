/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_int32.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 15:00:49 by sdarius-          #+#    #+#             */
/*   Updated: 2026/09/11 16:21:57 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	util_func(long *value, char *str, int sign, int i)
{
	int		digit;
	long	limit;

	digit = 0;
	if (sign == -1)
		limit = -(long)INT_MIN;
	else
		limit = INT_MAX;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		digit = str[i] - '0';
		if (*value > (limit - digit) / 10)
			return (1);
		*value = *value * 10 + digit;
		i++;
	}
	return (0);
}

int	ft_parse_int32(char *str, long *result)
{
	int		sign;
	long	value;
	int		i;

	i = 0;
	value = 0;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (str[i] == '\0')
		return (1);
	if (util_func(&value, str, sign, i) == 1)
		return (1);
	if (sign == -1)
		value = -value;
	*result = value;
	return (0);
}
