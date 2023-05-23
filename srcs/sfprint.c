/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sfprint.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <jopadova@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:51:19 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/22 11:58:00 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"
#include "minishell_error.h"
#include "minishell.h"


int	sfprint(char *s, bool newline)
{
	if (write(STDOUT_FILENO, s, ft_strlen(s)) == -1)
		return (-1);
	if (newline)
		if (write(STDOUT_FILENO, "\n", 1) == -1)
			return (-1);
	return (0);

}
