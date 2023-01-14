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

int	g_exit_code;

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

void	set_init_env(t_envnode **head, char **str)
{
	*head = NULL;
	*str = ft_calloc(1, 1);
}

void	set_oldpwd(t_envnode **head)
{
	t_envnode	*node;

	node = *head;
	while (node)
	{
		if (ft_strncmp(node->key, "OLDPWD", 7) == 0)
		{
			free(node->value);
			node->value = NULL;
			break ;
		}
		node = node->next;
	}
}

void	prt_exit(void)
{
	write(2, "exit\n", 5);
	exit(g_exit_code);
}
