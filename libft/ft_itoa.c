/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkwon <mkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:49:44 by mkwon             #+#    #+#             */
/*   Updated: 2022/05/21 13:37:24 by mkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countn(int n)
{
	int	cnt;

	cnt = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		cnt++;
		n = -n;
	}	
	while (n != 0)
	{
		n = n / 10;
		cnt++;
	}
	return (cnt);
}

static void	ntostr(char *str, int *i, int n)
{
	if (n < 0)
	{
		str[(*i)] = '-';
		(*i)++;
		n = -n;
	}
	if (n > 9)
	{
		ntostr(str, i, n / 10);
		ntostr(str, i, n % 10);
	}
	else
		str[(*i)++] = n + '0';
}

char	*ft_itoa(int n)
{
	char	*str;
	int		index;
	int		size;

	size = 0;
	index = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	size = countn(n);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (0);
	str[size] = 0;
	ntostr(str, &index, n);
	return (str);
}
