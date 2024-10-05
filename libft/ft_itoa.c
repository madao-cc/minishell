/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madao-da <madao-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 09:41:07 by madao-da          #+#    #+#             */
/*   Updated: 2023/10/10 14:28:33 by madao-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_digits(long n)
{
	long	i;

	i = 0;
	if (n == 0)
	{
		i = 1;
		return (i);
	}
	if (n < 0)
		n = n * -1;
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		lenght;
	char	*result;
	long	nbr;

	nbr = n;
	lenght = ft_digits(n);
	if (nbr < 0)
		lenght = lenght + 1;
	result = (char *)malloc(sizeof(char) * lenght + 1);
	if (!result)
		return (NULL);
	if (nbr < 0)
	{
		result[0] = '-';
		nbr = nbr * -1;
	}
	result[lenght] = '\0';
	while (nbr >= 10)
	{
		lenght--;
		result[lenght] = (nbr % 10) + 48;
		nbr = nbr / 10;
	}
	result[lenght - 1] = nbr + 48;
	return (result);
}
