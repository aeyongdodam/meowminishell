/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 18:09:50 by sohlee            #+#    #+#             */
/*   Updated: 2022/05/10 21:02:13 by sohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	if (!dst && !src)
		return (0);
	if (dst < src)
	{
		while (i < len)
		{
			((char *)dst)[i] = ((const char *)src)[i];
			i++;
		}
	}
	else
	{
		while (len != 0)
		{
			len--;
			((char *)dst)[len] = ((const char *)src)[len];
		}
	}
	return (dst);
}
