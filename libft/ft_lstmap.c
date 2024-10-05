/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madao-da <madao-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:19:00 by madao-da          #+#    #+#             */
/*   Updated: 2023/10/10 12:28:13 by madao-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*result;

	if (!lst || !f || !del)
		return (NULL);
	new = ft_lstnew(f(lst -> content));
	if (!new)
		return (NULL);
	result = new;
	lst = lst -> next;
	while (lst)
	{
		new -> next = ft_lstnew(f(lst -> content));
		if (new -> next == NULL)
		{
			ft_lstclear(&(new -> next), del);
			return (0);
		}
		new = new -> next;
		lst = lst -> next;
	}
	new -> next = NULL;
	return (result);
}
