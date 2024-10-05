/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madao-da <madao-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:05:49 by madao-da          #+#    #+#             */
/*   Updated: 2023/10/10 12:34:57 by madao-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int				lenght;
	unsigned char	ch;

	ch = (unsigned char)c;
	lenght = ft_strlen(str);
	while (str[lenght] != ch && lenght > 0)
		lenght--;
	if (str[lenght] == ch)
		return ((char *)str + lenght);
	return (0);
}
