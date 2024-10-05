/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madao-da <madao-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:22:13 by madao-da          #+#    #+#             */
/*   Updated: 2023/10/09 18:52:19 by madao-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *s1, void *s2, size_t n)
{
	unsigned char	*src;
	unsigned char	*dest;

	src = (unsigned char *)s2;
	dest = (unsigned char *)s1;
	if (!src && !dest)
		return (s1);
	if (src < dest)
	{
		while (n > 0)
		{
			*(dest + (n - 1)) = *(src + (n - 1));
			n--;
		}
	}
	while (n > 0)
	{
		*dest++ = *src++;
		n--;
	}
	return (s1);
}
