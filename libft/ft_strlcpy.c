/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkwon <mkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:02:50 by mkwon             #+#    #+#             */
/*   Updated: 2022/05/19 16:04:18 by mkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	change_str(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (1)
	{
		if (src[i] == 0)
		{
			dest[i] = 0;
			break ;
		}
		if (i == size - 1)
		{
			dest[i] = 0;
			break ;
		}
		dest[i] = src[i];
		i++;
	}
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size != 0)
		change_str(dest, src, size);
	while (src[i] != 0)
		i++;
	return (i);
}
