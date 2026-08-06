/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner_handle_errors_priv.h                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 21:21:06 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 21:21:07 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUNNER_HANDLE_ERRORS_PRIV_H
# define RUNNER_HANDLE_ERRORS_PRIV_H

# include "error.h"
# include "runner_type.h"

void	runner_handle_eof(t_error *err, bool interactive);
void	runner_handle_syntax_errors(
			t_runner *runner,
			t_error *err,
			bool interactive);
void	runner_handle_read_errors(t_error *err);
void	runner_handle_bad_errors(t_error *err, bool interactive);

#endif
