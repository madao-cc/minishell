/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madao-da <madao-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:40:12 by madao-da          #+#    #+#             */
/*   Updated: 2023/10/09 18:49:04 by madao-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*result;
	size_t	i;

	i = ft_strlen(str) + 1;
	result = malloc(i);
	if (!result)
		return (NULL);
	ft_memcpy(result, str, i);
	return (result);
}
