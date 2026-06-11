/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 16:27:18 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 16:27:56 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY__H
# define HISTORY__H

#include "history.h"

t_error	history_load_path_env(t_history *state);
t_error	history_load_size_env(t_history *state);

#endif
