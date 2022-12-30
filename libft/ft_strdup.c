/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohlee <sohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 12:55:25 by sohlee            #+#    #+#             */
/*   Updated: 2022/04/07 17:34:05 by sohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*dst;
	size_t	i;

	i = 0;
	len = ft_strlen(s1);
	dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (0);
	while (i < len)
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = 0;
	return (dst);
}
