#include "minishell_parse.h"

static const char		*g_symbol_name[] = {
	"invalid token", "<", ">", "<<", ">>", "|", "||", "&&", "(", ")", "\n",
	"word", "simple_cmd", "subshell_cmd"
};

static const u_int8_t	g_symbol_num[] = {
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	10,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	8,	9,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	1,	0,	2,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	5,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	3,	4,	7,	6,
	11
};

static const u_int8_t	g_act_table[] = {
	0,	0,	0,	0,	0,	7,	8,	9,	10,	11,
	0,	1,	2,	3,	4,	5,	0,	0,	0,	0,
};

int	tk_symbol(int tk)
{
	return ((int)g_symbol_num[tk]);
}

const char	*tk_translate(int tk)
{
	return (g_symbol_name[tk_symbol(tk)]);
}

int	parse(t_parser *p)
{
	while (p->state != PST_END)
	{
		if (!p->cmd_lst)
			parser_act(p, 6);
		p->tk = next_token(p, p->tk);
		if (p->tk < 0)
			break ;
		p->ssymc += tk_symbol(p->tk);
		p->act = g_act_table[p->ssymc];
		if (p->act)
		{
			parser_act(p, p->act);
			p->ssymc = 0;
		}
	}
	if (p->tk == EOF)
		p->eof = true;
	return (p->status);
}

void	reset_parser(t_parser *p)
{
	void	*tmp;

	if (p->cmd_line)
		add_history(p->cmd_line);
	ft_free(p->cmd_line);
	ft_free(p->line_read);
	while (p->cmd_lst)
	{
		tmp = p->cmd_lst->next;
		clean_cmd(p->cmd_lst);
		ft_free(p->cmd_lst);
		p->cmd_lst = (t_command_lst *)tmp;
	}
	while (p->hd_lst)
	{
		tmp = p->hd_lst->next;
		ft_free(p->hd_lst);
		p->hd_lst = (t_red *)tmp;
	}
	ft_memset(p, 0, sizeof (t_parser));
}