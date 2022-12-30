/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohlee <sohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 18:41:37 by sohlee            #+#    #+#             */
/*   Updated: 2022/04/07 19:00:36 by sohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	tmp;

	len = 0;
	tmp = (char) c;
	while (s[len] != 0)
		len++;
	if (tmp == 0)
		return ((char *) s + len);
	else
	{
		while (len >= 0)
		{
			if (s[len] == tmp)
				return ((char *)s + len);
			len--;
		}
	}
	return (0);
}
