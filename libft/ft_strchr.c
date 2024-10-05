/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madao-da <madao-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:38:08 by madao-da          #+#    #+#             */
/*   Updated: 2023/10/10 12:31:15 by madao-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int				i;
	unsigned char	ch;

	ch = (unsigned char)c;
	i = 0;
	while (str[i] != ch && str[i] != '\0')
		i++;
	if (str[i] == ch)
		return ((char *)str + i);
	return (0);
}
