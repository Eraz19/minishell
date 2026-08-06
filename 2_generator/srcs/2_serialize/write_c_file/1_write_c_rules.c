/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_write_c_rules.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:19:20 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 12:19:21 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "write_c_file_priv.h"
#include "generator_serialize_priv.h"
#include "logs.h"

#define RULE_VAR	"t_lr_rule\t\trules[RULE_COUNT]"

static inline bool	generator_write_c_rule(int c_fd, const t_rule *rule)
{
	if (!generator_write_zu(c_fd, NULL, rule->lhs))
		return (false);
	if (!generator_write(c_fd, ", "))
		return (false);
	return (generator_write_zu(c_fd, NULL, rule->rhs_len));
}

static inline bool	generator_write_all_rules(
						int c_fd,
						const t_lr_generator *gen)
{
	const t_rule	*rule;
	size_t			i;

	i = 0;
	while (i < RULE_COUNT)
	{
		if (!generator_write_brack_start(c_fd))
			return (false);
		rule = &gen->rules[i];
		if (!generator_write_c_rule(c_fd, rule))
			return (false);
		if (i < RULE_COUNT - 1)
		{
			if (!generator_write_brack_end(c_fd))
				return (false);
		}
		else if (!generator_write_brack_last(c_fd))
			return (false);
		i++;
	}
	return (true);
}

bool	generator_write_c_rules(int c_fd, const t_lr_generator *gen)
{
	if (!generator_write_c_var_start(c_fd, RULE_VAR))
		return (false);
	if (!generator_write_all_rules(c_fd, gen))
		return (false);
	if (!generator_write_c_var_end(c_fd))
		return (false);
	return (print_pass("rules generated\n"), true);
}
