/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:42:26 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:42:29 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Checks if variable c is a printable character
int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
