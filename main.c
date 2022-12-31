
#include "minishell.h"

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
	node->flag = 0;
	space = 0;
	while (*line)
	{
		if (*line == ' ')
		{
			if (space == 0 && str[0] != 0) //연속 space 제거
			{
				save_token(node, str, 1);
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
				save_token(node, str, 1);
				str = re_str(str);
			}
			node->right_child = init_node();
			node->right_child->flag = 2;
			node->right_child->token->str = ft_strdup("|");
			node = node->right_child;
			space = 0;
			pipe = 1;
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
		save_token(node, str, 1);
	}
	//prt_tree(tree->root, 0, 0);
	free(str);

	return (tree);
}

int main(int argc, char **argv, char *envp[])
{
	char	*line;
	int		ret;
	t_tree	*tree;

	set_terminal();
	while(1)
	{
		// printf("new\n");
		set_signal_handler(0);
		line = readline("\033[34mMinishell>\033[0m ");
		
		if (line)
        {
            //printf("output> %s\n", line);
			tree = lexer(line);
			main_pipe(tree, envp);
			// printf("*");
			add_history(line);
			free(line);
        }
        else
        {
            // printf("ctrl + d\n");
			exit(0);
        }
	}
	return (0);
}
