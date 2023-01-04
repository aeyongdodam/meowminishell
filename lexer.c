
#include "minishell.h"

char	*str_one_join(char *s1, char c)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = ft_strlen(s1);
	str = (char *)malloc(sizeof(char) * (len + 2));
	if (!str)
		return (0);
	while (i < len)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = 0;
	free(s1);
	return (str);
}

char	*re_str(char *str)
{
	free(str);
	str = malloc(1);
	str[0] = 0;
	return (str);
}

void	save_token(t_node *node, char *str, int flag)
{
	t_token	*token;

	if (node->left_child == NULL)
	{
		node->left_child = init_node();
		token = node->left_child->token;
		token->str = ft_strdup(str);
		token->flag = flag;
	}
	else
	{
		token = node->left_child->token;
		while (token->next)
			token = token->next;
		token->next = init_token();
		token->next->prev = token;
		token->next->str = ft_strdup(str);
		token->next->flag = flag;
	}
}

t_tree	*lexer(char	*line)
{
	t_tree	*tree;
	t_node	*node;
	char	*str;
	int		space;
	int		pipe;

	str = malloc(1);
	str[0] = 0;
	tree = init_tree();
	node = tree->root;
	node->token->flag = 0;
	space = 0;
	while (*line)
	{
		if (*line == ' ')
		{
			if (space == 0 && str[0] != 0) //연속 space 제거
			{
				save_token(node, str, WORD);
				str = re_str(str);
				space = 1;
				pipe = 0;
			}
		}
		else if (*line == '|')
		{
			if (pipe == 1)
			{
				exit(1);
				//연속된 파이프는 전부 에러처리함 ||이거도 | | 이거도
				// input : echo hi | | echo hello
				// ouput : bash: syntax error near unexpected token `|'
			}
			if (space == 0 && str) //space없이 바로 파이프
			{
				save_token(node, str, WORD);
				str = re_str(str);
			}
			node->right_child = init_node();
			node->right_child->token->flag = 2;
			node->right_child->token->str = ft_strdup("|");
			node = node->right_child;
			space = 0;
			pipe = 1;
			tree->pipe_cnt++;
		}
		else if (*line == '<' && *(line+1) == '<')
		{
			if (space == 0 && str) //space없이 바로 파이프
			{
				save_token(node, str, WORD);
				str = re_str(str);
			}
			save_token(node, "<<", HERE);
			line++;
		}
		else if (*line == '>' && *(line+1) == '>')
		{
			if (space == 0 && str) //space없이 바로 파이프
			{
				save_token(node, str, WORD);
				str = re_str(str);
			}
			save_token(node, ">>", REDI);
			line++;
		}
		else if (*line == '<')
		{
			if (space == 0 && str) //space없이 바로 파이프
			{
				save_token(node, "str", WORD);
				str = re_str(str);
			}
			save_token(node, "<", REDI);
		}
		else if (*line == '>')
		{
			if (space == 0 && str) //space없이 바로 파이프
			{
				save_token(node, "str", WORD);
				str = re_str(str);
			}
			save_token(node, ">", REDI);
		}
		else //word일때 차곡차곡 str에 담아요
		{
			str = str_one_join(str, line[0]);
			space = 0;
			pipe = 0;
		}
		line++;
	}
	if (str[0] != 0) //마지막 문자열
	{
		save_token(node, str, WORD);
	}
//	prt_tree(tree->root, 0, 0);
	free(str);
	return (tree);
}