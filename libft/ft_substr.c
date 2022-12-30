/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohlee <sohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 13:13:43 by sohlee            #+#    #+#             */
/*   Updated: 2022/05/11 16:28:45 by sohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	i;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (s_len <= len)
		dst = malloc(sizeof(char) * (s_len + 1));
	else
		dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (0);
	i = 0;
	while (i < len)
	{
		if (start + i >= s_len)
		{
			dst[i] = 0;
			break ;
		}
		else
			dst[i] = s[start + i];
		i++;
	}
	dst[i] = 0;
	return (dst);
}
