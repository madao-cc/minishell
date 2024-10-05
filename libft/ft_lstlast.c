/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madao-da <madao-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:10:21 by madao-da          #+#    #+#             */
/*   Updated: 2023/10/10 10:48:30 by madao-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*pointer;
	t_list	*last;

	if (!lst)
		return (NULL);
	pointer = lst;
	while (pointer -> next != NULL)
		pointer = pointer -> next;
	last = pointer;
	return (last);
}
