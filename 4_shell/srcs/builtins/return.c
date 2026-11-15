/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:41:35 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 21:23:07 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"

#define TOO_MANY_ARGS	"too many arguments"
#define NOT_UINT		"is not an unsigned decimal integer"
#define POSIX_CIT 		"POSIX: return: EXIT STATUS: the behavior is "
#define US_NOT_UINT		"unspecified if n is not an unsigned decimal integer"
#define US_TOO_BIG		"unspecified if n [...] is greater than 255"
#define ERR				"error"
#define MOD				"n % 256"

static inline t_error	return_too_many_args(
							const char *builtin_name,
							int *status)
{
	t_error	err;

	err = error(ERR_INVALID_USAGE);
	err = error_print(err, builtin_name, TOO_MANY_ARGS, NULL, NULL);
	*status = (int)err.type;
	err.type = ERR_POSIX_BUILTIN_SPECIAL;
	return (err);
}

static inline t_error	return_invalid_arg(
							const char *builtin_name,
							const char *arg,
							int *status)
{
	t_error	err;

	print_unspecified_behaviour(builtin_name, POSIX_CIT US_NOT_UINT, ERR);
	err = error(ERR_OPT_INVALID_ARG);
	err = error_print(err, builtin_name, arg, NOT_UINT, NULL, NULL);
	*status = (int)err.type;
	err.type = ERR_POSIX_BUILTIN_SPECIAL;
	return (err);
}

static inline t_error	return_no_arg(int *status)
{
	t_error	err;

	err = env_get_last_status(status);
	if (err.type)
	{
		*status = (int)err.type;
		return (err);
	}
	return (error(ERR_RETURN));
}

t_error	builtin_return(int argc, char **argv, t_runner *runner, int *status)
{
	int	first_operand_i;

	(void)runner;
	first_operand_i = 1;
	if (argc > 1 && str_cmp(argv[1], "--") == 0)
		first_operand_i++;
	if (argc - first_operand_i > 1)
		return (return_too_many_args(argv[0], status));
	if (first_operand_i >= argc)
		return (return_no_arg(status));
	if (!parse_int(argv[first_operand_i], status) || *status < 0)
		return (return_invalid_arg(argv[0], argv[first_operand_i], status));
	else if (*status > 255)
	{
		print_unspecified_behaviour(argv[0], POSIX_CIT US_TOO_BIG, MOD);
		*status %= 256;
	}
	return (error(ERR_RETURN));
}
