/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_build_name_priv.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:13:20 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:13:21 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_BUILD_NAME_PRIV_H
# define SIG_BUILD_NAME_PRIV_H

# include "sig_priv.h"
# include "error.h"

t_error	sig_build_name_set(const char *name, t_string *out_name);
t_error	sig_build_name_2(t_sig_id sig_id, t_string *out_name);

#endif
