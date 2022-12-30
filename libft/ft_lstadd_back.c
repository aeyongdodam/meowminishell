/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohlee <sohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 20:59:49 by sohlee            #+#    #+#             */
/*   Updated: 2022/05/11 15:24:35 by sohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (*lst)
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*lst = new;
}
