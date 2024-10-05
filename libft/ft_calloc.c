/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madao-da <madao-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 09:40:57 by madao-da          #+#    #+#             */
/*   Updated: 2023/10/09 18:34:34 by madao-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*result;

	result = malloc(nitems * size);
	if (!result)
		return (NULL);
	ft_bzero(result, (size * nitems));
	return (result);
}
