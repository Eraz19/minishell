/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_load_env_priv.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:09:10 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:09:11 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_LOAD_ENV_PRIV_H
# define HISTORY_LOAD_ENV_PRIV_H

# include <sys/types.h>

/* ************************************************************************* */
/*                                 ERROR                                     */
/* ************************************************************************* */

void	on_history_disabled_error(void);

/* ************************************************************************* */
/*                                 LOGS                                      */
/* ************************************************************************* */

void	history_load_max_size_from_unset_logs(void);

void	history_load_max_size_from_logs(ssize_t max);

void	history_load_max_size_from_invalid_logs(void);

void	history_load_max_size_from_out_of_range_logs(ssize_t max);

void	history_load_file_path_from_logs(const char *path, const char *origin);

#endif
