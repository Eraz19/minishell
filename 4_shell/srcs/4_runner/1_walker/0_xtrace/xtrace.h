/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xtrace.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:23:04 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:23:05 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XTRACE_H
# define XTRACE_H

# include "libft.h"
# include "error.h"

// prints a t_string
t_error	xtrace_print_one(const t_string *string);

// prints a vector of t_string
t_error	xtrace_print(const t_vector *expanded_strings);

// prints a vector of char*
t_error	xtrace_print_argv(const t_vector *argv);

#endif
