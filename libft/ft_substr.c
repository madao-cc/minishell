/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madao-da <madao-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:15:28 by madao-da          #+#    #+#             */
/*   Updated: 2023/10/10 14:29:55 by madao-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char			*result;
	unsigned int	size;

	if ((int)start >= ft_strlen(s))
		return (ft_strdup(""));
	if (!s)
		return (NULL);
	size = ft_strlen(s + start);
	if (size < len)
		len = size;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, s + start, len + 1);
	return (result);
}
