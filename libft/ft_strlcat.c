/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkwon <mkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 20:29:51 by mkwon             #+#    #+#             */
/*   Updated: 2022/05/19 16:49:13 by mkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_dest(char *dest)
{
	size_t	i;

	i = 0;
	while (dest[i] != 0)
		i++;
	return (i);
}

static size_t	count_src(char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != 0)
		i++;
	return (i);
}

static void	plus(char *dest, char *src, size_t size, size_t cnt_dest)
{
	size_t	i;

	i = 0;
	while (cnt_dest < size - 1 && src[i] != 0)
	{
		dest[cnt_dest] = src[i];
		cnt_dest++;
		i++;
	}
	dest[cnt_dest] = 0;
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	cnt_dest;
	size_t	cnt_src;

	cnt_dest = count_dest(dest);
	cnt_src = count_src((char *)src);
	if (cnt_dest >= size)
		return (cnt_src + size);
	else
	{
		plus(dest, (char *)src, size, cnt_dest);
		return (cnt_dest + cnt_src);
	}
}
