/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   break.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:41:18 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:41:19 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

#define TOO_MANY_ARGS	"too many arguments"
#define NOT_UINT		"is not an unsigned decimal integer "
#define NOT_UINT_2		"greater than or equal to 1"

static inline t_error	break_too_many_args(
							const char *builtin_name,
							int *exit_status)
{
	t_error	err;

	err = error(ERR_INVALID_USAGE);
	err = error_print(err, builtin_name, TOO_MANY_ARGS, NULL, NULL);
	*exit_status = (int)err.type;
	err.type = ERR_POSIX_BUILTIN_SPECIAL;
	return (err);
}

static inline t_error	break_invalid_arg(
							const char *builtin_name,
							const char *arg,
							int *exit_status)
{
	t_error	err;

	err = error(ERR_OPT_INVALID_ARG);
	err = error_print(err, builtin_name, arg, NOT_UINT NOT_UINT_2, NULL, NULL);
	*exit_status = (int)err.type;
	err.type = ERR_POSIX_BUILTIN_SPECIAL;
	return (err);
}

static inline t_error	break_no_arg(t_runner *runner, int *exit_status)
{
	runner->control_depth = 1;
	*exit_status = 0;
	return (error(ERR_BREAK));
}

t_error	builtin_break(int argc, char **argv, t_runner *runner, int *exit_status)
{
	int	first_operand_i;
	int	control_depth;

	first_operand_i = 1;
	if (argc > 1 && str_cmp(argv[1], "--") == 0)
		first_operand_i++;
	if (argc - first_operand_i > 1)
		return (break_too_many_args(argv[0], exit_status));
	if (first_operand_i >= argc)
		return (break_no_arg(runner, exit_status));
	if (!parse_int(argv[first_operand_i], &control_depth) || control_depth <= 0)
		return (break_invalid_arg(argv[0], argv[first_operand_i], exit_status));
	runner->control_depth = (size_t)control_depth;
	*exit_status = 0;
	return (error(ERR_BREAK));
}
