#ifndef PIPE_H
#define PIPE_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
typedef struct s_pipe{
	int	**fd;
	int pipe_cnt;
}t_pipe;

#endif