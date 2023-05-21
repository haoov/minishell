/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 16:35:46 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/21 17:40:47 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_builtins.h"

typedef struct s_echo
{
	int	word;
	int	no_new_line;
	int	param_end;
}	t_echo;

int	is_parameter(char *str, char param)
{
	if (*str++ != '-')
		return (0);
	while (*str == param)
		str++;
	if (*str != '\0')
		return (0);
	return (1);
}

int	b_echo(t_exec *e, int argc, char **argv)
{
	t_echo		info;

	(void)e;
	ft_memset(&info, 0, sizeof(t_echo));
	info.word++;
	while (info.word < argc)
	{
		if (is_parameter(argv[info.word], 'n') && !info.param_end)
		{
			info.word++;
			info.no_new_line = 1;
			continue ;
		}
		info.param_end = 1;
		printf("%s", argv[info.word]);
		if (info.word++ < argc - 1)
			printf(" ");
	}
	if (!info.no_new_line)
		printf("\n");
	return (0);
}