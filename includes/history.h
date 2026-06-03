/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 13:04:12 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/01 14:19:30 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include "error.h"
# include "../srcs/history/_history.h"

void	history_init(t_history *state);
void	history_free(t_history *state);
t_error	history_load(t_history *state, const char *path);

t_error	history_save_entry(void);
t_error	history_save_in_file(void);
t_error	history_append_to_entry(char *entry);

#endif
