#ifndef MINISHELL_EXECUTE_H
# define MINISHELL_EXECUTE_H

# include "minishell_command.h"
# include "libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_exec
{
	char	**env;
	int		tmpin;
	int		tmpout;
	int		*pipefd;
	int		infd;
	int		outfd;
	pid_t	pid_last;
	pid_t	pid_curr;
	int		child_nb;
	int		status;
}t_exec;

typedef struct s_builtin
{
	char	*cmd;
	int		(*ft)(t_exec *e, int argc, char **argv);
}t_builtin;

void	create_child(t_exec *e);
void	copy_word_list(t_command_lst *cl);
void	wait_childs(t_exec *e);

#endif