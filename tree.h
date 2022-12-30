#ifndef TREE_H
#define TREE_H
typedef struct s_token
{
	struct s_token	*next;
	struct s_token	*prev;
	char			*str;
	int				flag;
} t_token;

typedef struct s_tree
{
	t_token				*token;
	struct s_tree		*right_child;
	struct s_tree		*left_child;
} t_tree;

#endif
