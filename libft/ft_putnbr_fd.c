/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 21:59:48 by sohlee            #+#    #+#             */
/*   Updated: 2022/04/07 17:33:39 by sohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>

void	ft_putnbr(long long num, int fd)
{
	char	c;

	if (num == 0)
		return ;
	if (num > 0)
		ft_putnbr(num / 10, fd);
	c = num % 10 + '0';
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long long	num;

	num = n;
	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	if (num < 0)
	{
		write(fd, "-", 1);
		num *= -1;
	}
	ft_putnbr(num, fd);
}
