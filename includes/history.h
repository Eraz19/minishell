/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 13:04:12 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/08 11:38:22 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include "error.h"
# include "__history.h"

void	history_init(t_history *state);
void	history_free(t_history *state);
t_error	history_load(t_history *state, t_file_path path, ssize_t max);

t_error	history_save(void);
t_error	history_save_entry(void);
t_error	history_append_to_entry(char *entry);

#endif
