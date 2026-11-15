/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_error.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:40:32 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:55:23 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_ERROR_H
# define BUILTIN_ERROR_H

# include "error.h"

t_error	builtin_print_and_qualify(
			const char *builtin_name,
			t_error err,
			bool is_special_builtin,
			int *status);

#endif
