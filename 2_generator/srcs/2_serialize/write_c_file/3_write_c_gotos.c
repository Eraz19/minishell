/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_write_c_gotos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:19:25 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 22:39:31 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "write_c_file_priv.h"
#include "generator_serialize_priv.h"
#include "grammar_gotos.h"

#define GOTO_VAR	"size_t\t\t\tgotos[GOTO_COUNT]"

static inline bool	generator_write_all_gotos(
						int c_fd,
						const t_lr_generator *gen)
{
	size_t	col_count;
	size_t	count;
	size_t	i;

	col_count = SYM_NON_TERMINAL_MAX - SYM_NON_TERMINAL_MIN + 1;
	count = gen->lr_states.len * col_count;
	i = 0;
	while (i < count)
	{
		if (gen->gotos[i] == GOTO_EMPTY)
		{
			if (!generator_write(c_fd, "GOTO_EMPTY"))
				return (false);
		}
		else if (!generator_write_zu(c_fd, NULL, gen->gotos[i]))
			return (false);
		if (i < count - 1)
		{
			if (!generator_write(c_fd, ", "))
				return (false);
		}
		i++;
	}
	return (true);
}

bool	generator_write_c_gotos(int c_fd, const t_lr_generator *gen)
{
	if (!generator_write_c_var_start(c_fd, GOTO_VAR))
		return (false);
	if (!generator_write_all_gotos(c_fd, gen))
		return (false);
	if (!generator_write_c_var_end(c_fd))
		return (false);
	return (true);
}
