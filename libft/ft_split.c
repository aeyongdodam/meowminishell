/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohlee <sohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 20:59:46 by sohlee            #+#    #+#             */
/*   Updated: 2022/04/07 17:33:46 by sohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>

static void	ft_free(char	**dst)
{
	int	i;

	i = 0;
	while (dst[i] != 0)
		free(dst[i++]);
	return (free(dst));
}

static char	*put_str(char const *s, char c, char **dst)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (s[i] != 0 && s[i] != c)
		i++;
	tmp = (char *)malloc(sizeof(char) * (i + 1));
	if (tmp == 0)
	{
		ft_free(dst);
		return (tmp);
	}
	while (i-- > 0)
	{
		tmp[j] = s[j];
		j++;
	}
	tmp[j] = 0;
	return (tmp);
}

static int	word_cnt(char const *s, char c)
{
	int	rtn;
	int	i;

	rtn = 0;
	i = 0;
	while (s[i] != 0)
	{
		while (s[i] == c && s[i] != 0)
			i++;
		if (s[i] != 0)
		{
			rtn++;
			i++;
		}
		while (s[i] != c && s[i] != 0)
			i++;
	}
	return (rtn);
}

char	**ft_split(char const *s, char c)
{
	char	**dst;
	int		cnt;
	int		i;

	i = 0;
	cnt = word_cnt(s, c);
	dst = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (!dst)
		return (0);
	while (*s != 0)
	{
		while (*s != 0 && *s == c)
			s++;
		if (*s != 0)
		{
			dst[i] = put_str(s, c, dst);
			if (dst[i] == 0)
				return (0);
			i++;
		}
		while (*s != 0 && *s != c)
			s++;
	}
	dst[i] = 0;
	return (dst);
}
