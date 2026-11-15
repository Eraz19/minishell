/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   posix_open_priv.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:43:26 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 12:43:27 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POSIX_OPEN_PRIV_H
# define POSIX_OPEN_PRIV_H

# include "error.h"
# include <sys/stat.h>

t_error	open_check_ub_args(int oflag, mode_t *optional_mode);

#endif
