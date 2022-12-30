/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohlee <sohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 21:17:49 by sohlee            #+#    #+#             */
/*   Updated: 2022/05/11 16:09:52 by sohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (1)
	{
		f(lst->content);
		if (lst->next != 0)
		{
			lst = lst -> next;
		}
		else
			break ;
	}
}
