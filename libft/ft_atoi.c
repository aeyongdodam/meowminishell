/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohlee <sohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 22:13:03 by sohlee            #+#    #+#             */
/*   Updated: 2022/04/02 22:22:34 by sohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	check_range(unsigned long long ans, int sign)
{
	if (ans > 9223372036854775807 - 1 && sign == -1)
		return (0);
	if (ans > 9223372036854775807 - 1 && sign == 1)
		return (-1);
	return (ans * sign);
}

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	ans;
	int					sign;

	i = 0;
	ans = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		ans = ans * 10 + (str[i] - '0');
		i++;
	}
	return (check_range(ans, sign));
}
