/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohlee <sohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 21:19:31 by sohlee            #+#    #+#             */
/*   Updated: 2022/05/10 22:45:09 by sohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*tmp;

	new_list = 0;
	while (1)
	{
		tmp = malloc(sizeof(t_list));
		tmp->content = f(lst->content);
		tmp->next = 0;
		if (!tmp)
		{
			ft_lstclear(&new_list, del);
			return (0);
		}
		ft_lstadd_back(&new_list, tmp);
		if (lst->next != 0)
			lst = lst->next;
		else
			break ;
	}
	return (new_list);
}
