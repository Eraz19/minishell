/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_separator_op.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:42:10 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/04 16:42:11 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator_rules_priv.h"

static void	rules_build_separator_op_1(t_rule *rules);
static void	rules_build_separator_op_2(t_rule *rules);

/*
separator_op     : '&'
                 | ';'
                 ;
*/
void	rules_build_separator_op(t_rule *rules)
{
	rules_build_separator_op_1(rules);
	rules_build_separator_op_2(rules);
}

// separator_op -> '&'
static void	rules_build_separator_op_1(t_rule *rules)
{
	rules[RULE_SEPARATOR_OP_1].lhs = SYM_separator_op;
	rules[RULE_SEPARATOR_OP_1].rhs[0] = SYM_AMPERSAND;
	rules[RULE_SEPARATOR_OP_1].rhs_len = 1;
}

// separator_op -> ';'
static void	rules_build_separator_op_2(t_rule *rules)
{
	rules[RULE_SEPARATOR_OP_2].lhs = SYM_separator_op;
	rules[RULE_SEPARATOR_OP_2].rhs[0] = SYM_SEMI;
	rules[RULE_SEPARATOR_OP_2].rhs_len = 1;
}
