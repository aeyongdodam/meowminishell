/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkwon <mkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 17:55:47 by mkwon             #+#    #+#             */
/*   Updated: 2022/05/21 17:05:22 by mkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	find_start(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;

	i = 0;
	start = 0;
	while (s1[i] != 0 && ft_strchr(set, s1[i]))
	{
		start = i + 1;
		i++;
	}
	return (start);
}

static size_t	find_end(char const *s1, char const *set, size_t start)
{
	size_t	i;
	size_t	end;

	end = ft_strlen(s1) - 1;
	i = end;
	while (i >= start && ft_strchr(set, s1[i]))
	{
		end = i - 1;
		i--;
	}
	return (end);
}

static void	fill_str(char *str, char const *s1, size_t start, size_t end)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s1[i] != 0)
	{
		if (i >= start && i <= end)
		{
			str[j] = s1[i];
			j++;
		}
		i++;
	}
	str[j] = 0;
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		start;
	size_t		end;
	char		*str;

	if (!s1)
		return (0);
	if (s1[0] == 0
		|| find_start(s1, set) > find_end(s1, set, find_start(s1, set)))
	{
		str = (char *)malloc(1);
		if (!str)
			return (0);
		str[0] = 0;
		return (str);
	}
	start = find_start(s1, set);
	end = find_end(s1, set, start);
	str = (char *)malloc(sizeof(char) * (end - start + 2));
	if (!str)
		return (0);
	fill_str(str, s1, start, end);
	return (str);
}
