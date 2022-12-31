/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkwon <mkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 22:01:44 by mkwon             #+#    #+#             */
/*   Updated: 2022/05/21 16:54:13 by mkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	counts(const char *s, char c)
{
	int	cnt;
	int	i;

	cnt = 0;
	i = 0;
	while (s[i] != 0)
	{
		if (s[i] != c)
		{
			cnt++;
			while (s[i] != c && s[i] != 0)
				i++;
		}
		else
			i++;
	}
	return (cnt);
}

static char	*ft_strncpy(char *D, const char *S, unsigned int s, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (s < n)
	{
		D[i] = S[s];
		i++;
		s++;
	}
	D[i] = 0;
	return (D);
}

static char	**free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != 0)
		free (split[i]);
	free (split);
	return (0);
}

static int	help_split(char **split_j, const char *s, char c, int *i)
{
	int	size;

	size = *i;
	while (s[size] != c && s[size] != 0)
		size++;
	(*split_j) = (char *)malloc(sizeof(char) * (size - (*i) + 1));
	if (!(*split_j))
		return (0);
	(*split_j) = ft_strncpy((*split_j), s, *i, size);
	*i = size;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		size;
	char	**split;

	i = 0;
	j = 0;
	size = counts(s, c);
	split = (char **)malloc(sizeof(char *) * (size + 1));
	if (!split)
		return (0);
	split[size] = 0;
	while (j < size)
	{
		if (s[i] != c)
		{
			if (help_split((split + j), s, c, &i) == 0)
				return (free_split(split));
			j++;
		}
		else
			i++;
	}
	return (split);
}
