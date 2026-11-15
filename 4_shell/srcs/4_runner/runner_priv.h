/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner_priv.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:24:03 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:24:04 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUNNER_PRIV_H
# define RUNNER_PRIV_H

# include "error.h"
# include "runner_type.h"

// TODO: doc
void	runner_handle_error(t_runner *runner, t_error *err);

#endif
