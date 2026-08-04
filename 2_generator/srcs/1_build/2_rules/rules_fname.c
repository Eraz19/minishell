/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_fname.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:41:14 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/04 16:41:15 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator_rules_priv.h"

/*
fname            : NAME (apply rule 8)
                 ;
⚠️ Bash-like parser adaptation: function name is parsed as WORD,
	then validated as a POSIX name during reduction.
	(see hook_fname())
*/
void	rules_build_fname(t_rule *rules)
{
	rules[RULE_FNAME_1].lhs = SYM_fname;
	rules[RULE_FNAME_1].rhs[0] = SYM_WORD;
	rules[RULE_FNAME_1].rhs_len = 1;
}
