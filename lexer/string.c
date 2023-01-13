
#include "../minishell.h"

char	*str_one_join(char *s1, char c, t_tree *tree, int flag)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = ft_strlen(s1);
	str = ft_calloc(len + 2, 1);
	while (i < len)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = 0;
	free(s1);
	if (flag == 1)
		set_variable(tree, 0, 0, 0);
	return (str);
}

char	*re_str(char *str)
{
	free(str);
	str = ft_calloc(1, 1);
	if (!str)
		return (0);
	return (str);
}

char	*re_str_join(char **str, char **s)
{
	char	*temp;

	temp = ft_strjoin(*str, *s);
	free(*str);
	free(*s);
	return (temp);
}
