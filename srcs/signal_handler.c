#include "minishell.h"
#include "minishell_parse.h"

t_data	*g_msh;

void	handle_sigabrt(int signum)
{
	(void)signum;
/*	ft_putstr_fd(ABRTMSG, 2);
	ft_putchar_fd('\n', 2);*/
	clean_all(g_msh);
	exit(EXS_SIGSEG);
}

void	signal_handler(t_data *msh)
{
	g_msh = msh;
	signal(SIGABRT, handle_sigabrt);
//	signal(SIGINT, handle_sigint);
//	signal(SIGQUIT, handle_sigquit);
}