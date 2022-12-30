/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkwon <mkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 14:49:48 by mkwon             #+#    #+#             */
/*   Updated: 2022/05/21 10:35:45 by mkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int			i;
	char		*temp;

	i = 0;
	temp = 0;
	if ((unsigned char)c == 0)
		temp = (char *)&s[ft_strlen(s)];
	while (s[i] != 0)
	{
		if (s[i] == (unsigned char)c)
			temp = (char *)&s[i];
		i++;
	}
	return (temp);
}
