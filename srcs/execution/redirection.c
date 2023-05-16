#include "minishell.h"

int		mod_redir(t_exec *e, t_red *r);
void	do_pipe_red(t_exec *e, t_command cmd);

int	do_redir(t_exec *e, t_command cmd)
{
	do_ft(DUP2, &e->tmpin, STDIN_FILENO);
	do_ft(DUP2, &e->tmpout, STDOUT_FILENO);
	if (cmd.flags & CMD_PIPE)
		do_pipe_red(e, cmd);
	while (cmd.reds)
	{
		if (mod_redir(e, cmd.reds))
			return (-1);
		cmd.reds = cmd.reds->next;
	}
	if (e->infd)
	{
		do_ft(DUP2, &e->infd, STDIN_FILENO);
		do_ft(CLOSE, &e->infd, 0);
	}
	if (e->outfd)
	{
		do_ft(DUP2, &e->outfd, STDOUT_FILENO);
		do_ft(CLOSE, &e->outfd, 0);
	}
	return (0);
}

void	do_pipe_red(t_exec *e, t_command cmd)
{
	if (!(cmd.flags & CMD_STARTPIPE))
	{
		do_ft(DUP2, &e->pipefd[0], STDIN_FILENO);
		do_ft(CLOSE, &e->pipefd[0], 0);
	}
	if (!(cmd.flags & CMD_ENDPIPE))
	{
		do_ft(PIPE, e->pipefd, 0);
		e->outfd = e->pipefd[1];
	}
}

int	mod_redir(t_exec *e, t_red *r)
{
/*	if (!expand_red(r->filename))
		return (print_error(REDAMB, r->filename->lval));*/
	if (r->rflags & RED_IN)
	{
		if (e->infd)
			do_ft(CLOSE, &e->infd, 0);
/*		if (r->rflags & RED_HEREDOC)
			e->infd = heredoc(r);*/
		else
			e->infd = open(r->filename->lval, r->oflags, 0664);
		if (e->infd == -1)
			return (print_error(strerror(errno), r->filename->lval));

	}
	if (r->rflags & RED_OUT)
	{
		if (e->outfd)
			do_ft(CLOSE, &e->outfd, 0);
		e->outfd = open(r->filename->lval, r->oflags, 0664);
		if (e->outfd == -1)
			return (print_error(strerror(errno), r->filename->lval));
	}
	return (0);
}

void	close_all(t_exec *e)
{
	do_ft(CLOSE, &e->tmpin, 0);
	do_ft(CLOSE, &e->tmpout, 0);
	do_ft(CLOSE, &e->infd, 0);
	do_ft(CLOSE, &e->outfd, 0);
	do_ft(CLOSE, &e->pipefd[0], 0);
	do_ft(CLOSE, &e->pipefd[1], 0);
}
