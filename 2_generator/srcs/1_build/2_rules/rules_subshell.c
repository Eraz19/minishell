/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:42:23 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/04 16:42:24 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator_rules_priv.h"

/*
subshell         : '(' compound_list ')'
                 ;
*/
void	rules_build_subshell(t_rule *rules)
{
	rules[RULE_SUBSHELL_1].lhs = SYM_subshell;
	rules[RULE_SUBSHELL_1].rhs[0] = SYM_LPARENTHESIS;
	rules[RULE_SUBSHELL_1].rhs[1] = SYM_compound_list;
	rules[RULE_SUBSHELL_1].rhs[2] = SYM_RPARENTHESIS;
	rules[RULE_SUBSHELL_1].rhs_len = 3;
}
