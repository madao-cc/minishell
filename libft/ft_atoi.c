/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madao-da <madao-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 09:40:44 by madao-da          #+#    #+#             */
/*   Updated: 2023/10/09 18:48:50 by madao-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nbr)
{
	int	sign;
	int	result;

	while (*nbr == ' ' || (*nbr >= 9 && *nbr <= 13))
		nbr++;
	if (*nbr == '+' || *nbr == '-')
	{
		if (*nbr == '-')
			sign = 1;
		nbr++;
	}
	result = 0;
	while (*nbr >= '0' && *nbr <= '9')
	{
		result = result * 10 + (*nbr - 48);
		nbr++;
	}
	if (sign == 1)
		return (result * -1);
	return (result);
}
