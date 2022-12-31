/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkwon <mkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 14:33:50 by mkwon             #+#    #+#             */
/*   Updated: 2022/05/20 12:06:32 by mkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	*temp;

	i = 0;
	temp = (unsigned char *)s;
	while (temp[i] != 0)
	{
		if (temp[i] == (unsigned char)c)
			return ((char *)&temp[i]);
		i++;
	}
	if ((unsigned char)c == 0)
		return ((char *)&temp[i]);
	return (0);
}
