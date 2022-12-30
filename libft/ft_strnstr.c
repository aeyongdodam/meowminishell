/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohlee <sohlee@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 20:25:32 by sohlee            #+#    #+#             */
/*   Updated: 2022/05/10 21:31:15 by sohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	n_len;

	j = 0;
	n_len = ft_strlen(needle);
	if (len == 0 && *haystack == 0)
		return ((char *)haystack);
	if (*needle == 0)
		return ((char *)haystack);
	while (haystack[j] != 0 && j < len)
	{
		i = 0;
		while (haystack[i + j] == needle[i] && (i + j < len))
		{
			if (needle[i + 1] == 0)
				return ((char *)haystack + j);
			i++;
		}
		j++;
	}
	return (0);
}
