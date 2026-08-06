/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_parse_name_priv.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:13:44 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:13:45 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_PARSE_NAME_PRIV_H
# define SIG_PARSE_NAME_PRIV_H

# include "sig_priv.h"
# include "error.h"

t_error	sig_parse_name_set(
			int signo,
			t_sig_id sig_id,
			int *out_signo,
			t_sig_id *out_sig_id);
t_error	sig_parse_name_2(
			const char *name,
			int *out_signo,
			t_sig_id *out_sig_id);

#endif
