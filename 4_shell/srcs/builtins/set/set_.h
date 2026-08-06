/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:41:10 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:54:25 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET__H
# define SET__H

# include "error.h"
# include "options.h"
# include "ft_getopt.h"

# define SET_USAGE_1	"set [-abCefhmnuvx] [-o option] [argument...]\n"
# define SET_USAGE_2	"set [+abCefhmnuvx] [+o option] [argument...]\n"
# define SET_USAGE_3	"set -- [argument...]\n"
# define SET_USAGE_4	"set -o\n"
# define SET_USAGE_5	"set +o\n"

t_error	set_print_options(char sign);
t_error	set_print_one(char sign, const char *name, bool on);
bool	set_named_option(size_t i, const char **name, t_option *bit);
t_error	set_apply_options(t_getopt_out *out, size_t argc, char **argv);

#endif
