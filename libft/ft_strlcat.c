/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohlee <sohlee@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:50:39 by sohlee            #+#    #+#             */
/*   Updated: 2022/05/11 16:01:50 by sohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<string.h>

static size_t	ft_len(const char	*str)
{
	size_t	i;

	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;

	i = 0;
	dst_len = ft_len(dst);
	src_len = ft_len(src);
	if (dst_len >= dstsize)
		return (src_len + dstsize);
	else
	{
		while (i < dstsize - dst_len - 1 && src[i] != '\0')
		{
			dst[dst_len + i] = src[i];
			i++;
		}
		dst[dst_len + i] = '\0';
	}
	return (dst_len + src_len);
}
