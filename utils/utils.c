/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkwon <mkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 23:21:23 by mkwon             #+#    #+#             */
/*   Updated: 2023/01/12 23:21:26 by mkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	prt_meows(void)
{
	int		fd;
	int		n;
	char	*buf;

	fd = open("utils/meow.txt", O_RDONLY);
	buf = ft_calloc(2, 1);
	while (read(fd, buf, 1) > 0)
	{
		printf("%s", buf);
	}
	printf("\n");
	free(buf);
}

int	error_redi_fun1(t_node *node)
{
	if (node->token->flag == WORD)
		return (1);
	if (node->token->flag == REDI)
		return (1);
	if (node->token->flag == HERE)
		return (1);
	return (0);
}

int	error_redi_fun2(t_token *token)
{
	if (token->next == NULL)
	{
		prt_error(2, 0);
		return (1);
	}
	else if (token->next->flag == REDI || token->next->flag == HERE)
	{
		prt_error(1, token->next->str);
		return (1);
	}
	return (0);
}

void	set_init_env(t_envnode **head, char **str)
{
	*head = NULL;
	*str = ft_calloc(1, 1);
}
