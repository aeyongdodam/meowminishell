/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohlee <sohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 13:31:42 by sohlee            #+#    #+#             */
/*   Updated: 2022/04/07 17:34:16 by sohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	dst = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!dst)
		return (0);
	i = 0;
	while (i < s1_len)
	{
		dst[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < s2_len)
	{
		dst[i + s1_len] = s2[i];
		i++;
	}
	dst[s1_len + s2_len] = 0;
	return (dst);
}
