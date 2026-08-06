/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_sig_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:14:09 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 15:14:05 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig.h"
#include "sig_priv.h"
#include "posix_helpers.h"
#include <unistd.h>

// @ret ERR_NO / ERR_INTERNAL / ERR_POSIX_WRITE / ERR_LIBC
static inline t_error	sig_print_one(t_sig_action *action, t_sig_id sig_id)
{
	t_string	out;
	t_error		err;

	err = sig_build_output(action, sig_id, &out);
	if (err.type)
		return (err);
	err = posix_write(STDOUT_FILENO, out.data, out.len);
	string_free(&out);
	return (err);
}

static inline t_error	sig_print_and_absorb(
							t_error err,
							const char *builtin_name,
							const char *arg,
							int *exit_status)
{
	*exit_status = (int)err.type;
	(void)error_print(err, builtin_name, arg, NULL, NULL);
	return (error(ERR_NO));
}

t_error	sig_print_conditions(
			const char *name,
			char **conditions,
			int *status)
{
	t_sig_state	*sig_state;
	size_t		i;
	t_sig_id	sig_id;
	int			signo;
	t_error		err;

	err = sig_get_printable_state(&sig_state);
	i = 0;
	while (err.type == ERR_NO && conditions[i] != NULL)
	{
		if (!str_cmp(conditions[i], "EXIT") || !str_cmp(conditions[i], "0"))
			err = sig_print_one(&sig_state->exit_action, SIG_EXIT_ID);
		else
		{
			err = sig_parse_name(conditions[i], &signo, &sig_id);
			if (err.type == ERR_NO)
				err = sig_print_one(&sig_state->actions[sig_id], sig_id);
			else
				err = sig_print_and_absorb(err, name, conditions[i], status);
		}
		i++;
	}
	return (err);
}

// trap -p
t_error	sig_print_all(void)
{
	t_sig_state	*sig_state;
	t_sig_id	sig_id;
	t_error		err;

	err = sig_get_printable_state(&sig_state);
	if (err.type)
		return (err);
	sig_id = 0;
	while (sig_id < SIG_ID_COUNT)
	{
		err = sig_print_one(&sig_state->actions[sig_id], sig_id);
		if (err.type)
			return (err);
		sig_id++;
	}
	return (sig_print_one(&sig_state->exit_action, SIG_EXIT_ID));
}

// trap
t_error	sig_print_all_except_default(void)
{
	t_sig_state		*sig_state;
	t_sig_id		sig_id;
	t_sig_action	*action;
	t_error			err;

	err = sig_get_printable_state(&sig_state);
	if (err.type)
		return (err);
	sig_id = 0;
	while (sig_id < SIG_ID_COUNT)
	{
		action = &sig_state->actions[sig_id];
		if (action->type != SIG_DEFAULT)
		{
			err = sig_print_one(action, sig_id);
			if (err.type)
				return (err);
		}
		sig_id++;
	}
	if (sig_state->exit_action.type != SIG_DEFAULT)
		return (sig_print_one(&sig_state->exit_action, SIG_EXIT_ID));
	return (err);
}
