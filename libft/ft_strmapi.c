/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohlee <sohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 21:46:55 by sohlee            #+#    #+#             */
/*   Updated: 2022/04/07 17:35:14 by sohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*dst;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s);
	dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (0);
	while (i < len)
	{
		dst[i] = f(i, s[i]);
		i++;
	}
	dst[i] = 0;
	return (dst);
}
