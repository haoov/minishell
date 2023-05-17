#include <stdlib.h>
#include "minishell.h"

int		exec_cmd_lst(t_data *msh, t_exec *e, t_command_lst *cl);
void	init_env(t_exec *e);

int	main(int argc, char **argv)
{
	t_data	*msh;
	int		status;

	if (argc != 1 || !argv)
		return (EXIT_FAILURE);
	msh = (t_data *)sfcalloc(1, sizeof (t_data));
	init_env(&msh->exec);
	signal_handler(msh);
	while (!msh->parser.eof)
	{
		reset_parser(&msh->parser);
		status = parse(&msh->parser);
		if (status)
			continue ;
		status = exec_cmd_lst(msh, &msh->exec, msh->parser.cmd_lst);
	}
	clean_all(msh);
	return (status);
}

int	exit_prg(t_data *msh, int status)
{
	clean_all(msh);
	exit(status);
}