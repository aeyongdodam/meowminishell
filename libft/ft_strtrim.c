/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohlee <sohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 13:48:54 by sohlee            #+#    #+#             */
/*   Updated: 2022/05/11 16:28:11 by sohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	i;
	char	*dst;

	dst = 0;
	start = 0;
	i = 0;
	end = ft_strlen(s1) - 1;
	while (start <= end && s1[start] != 0 && ft_strchr(set, s1[start]) != 0)
		start++;
	while (end > 0 && s1[end] != 0 && ft_strchr(set, s1[end]) != 0)
		end--;
	if (start == ft_strlen(s1))
		return (ft_strdup(""));
	dst = malloc(sizeof(char) * (end - start + 2));
	if (!dst)
		return (NULL);
	while (start <= end)
		dst[i++] = s1[start++];
	dst[i] = 0;
	return (dst);
}
