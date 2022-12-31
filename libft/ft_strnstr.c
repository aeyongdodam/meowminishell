/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkwon <mkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 15:38:42 by mkwon             #+#    #+#             */
/*   Updated: 2022/05/20 10:18:34 by mkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;
	char	*s;
	char	*t;

	i = 0;
	s = (char *)str;
	t = (char *)to_find;
	if (*to_find == 0)
		return (s);
	while (i < len && s[i] != 0)
	{
		j = 0;
		while (t[j] == s[i + j] && i + j < len)
		{
			j++;
			if (t[j] == 0)
				return (&s[i]);
		}
		i++;
	}
	return (0);
}
