/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spash.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 18:17:36 by rsabbah           #+#    #+#             */
/*   Updated: 2023/04/14 18:55:07 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPASH_H
# define SPASH_H

# include "spash_types.h"
# include <stdbool.h>

void	init(t_data *data);
void	reset(t_data *data);

void	sig(t_data *data);

int		spash(t_data *data, bool subcmd);

void	cleanup(t_data *data, bool all);
void	clean_tokens(t_data *data);

int		exit_prg(t_data *data);

#endif
