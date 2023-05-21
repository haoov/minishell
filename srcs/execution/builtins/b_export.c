/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 16:53:29 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/21 18:54:24 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_builtins.h"

char	**edit_in_env(char *var, char *full_var, t_exec *e)
{
	int		i;
	int		j;
	int		env_size;
	char	**tmp_env;

	j = -1;
	i = get_env_index(e->env, var);
	env_size = 0;
	while (e->env && e->env[env_size])
		env_size++;
	tmp_env = (char **)sfcalloc(env_size + 1, sizeof (char *));
	while (++j < env_size)
		tmp_env[j] = e->env[j];
	free(tmp_env[i]);
	tmp_env[i] = full_var;
	free(e->env);
	return (tmp_env);
}

char	**add_in_env(char *full_var, t_exec *e)
{
	int		j;
	int		env_size;
	char	**tmp_env;

	j = -1;
	env_size = 0;
	while (e->env && e->env[env_size])
		env_size++;
	tmp_env = (char **)sfcalloc(env_size + 2, sizeof (char *));
	while (++j < env_size)
		tmp_env[j] = e->env[j];
	tmp_env[env_size] = full_var;
	tmp_env[env_size + 1] = NULL;
	free(e->env);
	return (tmp_env);
}

void	msh_export_one(char *name, char *value, t_exec *e)
{
	char	*full_var;
	char	*tmp_full_var;

	if (!name || !value)
		return ;
	tmp_full_var = ft_strjoin(name, "=");
	if (!tmp_full_var)
		return (free(name), (void) malloc_error());
	full_var = ft_strjoin(tmp_full_var, value);
	free(tmp_full_var);
	if (!full_var)
		return (free(name), (void) malloc_error());
	if (getenv(name))
		e->env = edit_in_env(name, full_var, e);
	else
		e->env = add_in_env(full_var, e);
	__environ = e->env;
}

static int	is_env_name(char c)
{
	if (!ft_isalnum(c) && c != '_')
		return (0);
	return (1);
}

#define EXPORTFAIL "not a valid identifier"

int	b_export(t_exec *e, int argc, char **argv)
{
	int		i;
	int		j;
	char	*name;

	i = 1;
	while (i < argc && argv[i])
	{
		name = sfcalloc(ft_strlen(argv[i]), sizeof(char));
		j = 0;
		while (*argv[i] != '=')
		{
			if (!is_env_name(*argv[i]))
				return (free(name), print_error(EXPORTFAIL, "export", NULL));
			name[j++] = *argv[i]++;
		}
		msh_export_one(name, ++argv[i], e);
		free(name);
		i++;
	}
	return (EXIT_SUCCESS);
}