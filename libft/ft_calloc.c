/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohlee <sohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 22:13:55 by sohlee            #+#    #+#             */
/*   Updated: 2022/05/02 22:39:40 by sohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*a;

	if (size != 0)
	{
		if (count >= SIZE_MAX / size)
			return (0);
	}
	a = malloc(count * size);
	if (!a)
		return (0);
	ft_bzero(a, (count * size));
	return (a);
}
