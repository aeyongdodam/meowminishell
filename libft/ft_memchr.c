/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohlee <sohlee@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 18:52:45 by sohlee            #+#    #+#             */
/*   Updated: 2022/04/07 17:32:25 by sohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*a;
	unsigned char	b;

	a = (unsigned char *)s;
	b = c;
	i = 0;
	while (i < n)
	{
		if (*a == b)
			return ((void *)a);
		a++;
		i++;
	}
	return (0);
}
