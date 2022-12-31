#ifndef TREE_H
#define TREE_H

#define WOED 0
#define PIPE 1
#define RIDI 2

typedef struct s_token
{
	struct s_token	*next;
	struct s_token	*prev;
	char			*str;
} t_token;

typedef struct s_node
{
	t_token				*token;
	int				flag;
	struct s_node		*right_child;
	struct s_node		*left_child;
} t_node;

#endif
