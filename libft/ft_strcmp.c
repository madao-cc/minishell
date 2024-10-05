/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madao-da <madao-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:58:56 by madao-da          #+#    #+#             */
/*   Updated: 2023/10/09 18:56:49 by madao-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	if (i >= n)
		return (0);
	while (*str1 && *str1 == *str2 && i < n)
	{
		str1++;
		str2++;
		i++;
	}
	return (*str1 - *str2);
}
