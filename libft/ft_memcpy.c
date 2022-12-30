/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohlee <sohlee@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 22:23:26 by sohlee            #+#    #+#             */
/*   Updated: 2022/05/02 20:05:49 by sohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*a;
	unsigned char	*b;
	size_t			i;

	a = (unsigned char *)src;
	b = dst;
	i = 0;
	if (dst == 0 && src == 0)
		return (0);
	while (i < n)
	{
		b[i] = a[i];
		i++;
	}
	return (dst);
}
