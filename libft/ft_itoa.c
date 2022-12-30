/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohlee <sohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 21:32:10 by sohlee            #+#    #+#             */
/*   Updated: 2022/04/07 17:31:57 by sohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_size(long long num)
{
	int	rtn;

	rtn = 0;
	if (num == 0)
		return (1);
	if (num < 0)
	{
		rtn++;
		num *= -1;
	}
	while (num > 0)
	{
		num /= 10;
		rtn++;
	}
	return (rtn);
}

char	*ft_itoa(int n)
{
	char		*dst;
	long long	num;
	int			size;
	int			i;

	num = n;
	size = ft_size(num);
	i = 0;
	dst = malloc(sizeof(char) * (size + 1));
	if (!dst)
		return (0);
	if (num < 0)
	{
		num *= -1;
		dst[0] = '-';
		i++;
	}
	dst[size--] = 0;
	while (size >= i)
	{
		dst[size--] = num % 10 + '0';
		num /= 10;
	}
	return (dst);
}
