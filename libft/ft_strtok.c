/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:49:51 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/10/14 15:50:10 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strtok(char *str, const char *delim)
{
	static char *save = NULL;
	char *token;
	char *tmp;

	if (str)
		save = str;
	if (!save)
		return (NULL);
	token = save;
	if (!(tmp = ft_strpbrk(save, delim)))
		save = NULL;
	else
	{
		*tmp = '\0';
		save = tmp + 1;
	}
	return (token);
}