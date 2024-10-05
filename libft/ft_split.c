/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madao-da <madao-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:28:59 by madao-da          #+#    #+#             */
/*   Updated: 2023/10/10 14:29:09 by madao-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_words(const char *s, char c)
{
	size_t	i;
	size_t	words;

	words = 0;
	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			words++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		else
		{
			i++;
		}
	}
	return (words);
}

static int	ft_word_len(const char *s, char i)
{
	int	a;

	a = 0;
	while (s[a] != i && s[a] != '\0')
		a++;
	return (a);
}

char	**ft_split(const char *s, char c)
{
	char		**result;
	size_t		i;
	size_t		word;

	result = (char **)malloc(sizeof(char *) * (ft_words(s, c) + 1));
	if (!result)
		return (NULL);
	word = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != '\0')
		{
			result[word] = ft_substr(s, (i), ft_word_len(s + i, c));
			word++;
		}
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	result[word] = NULL;
	return (result);
}
