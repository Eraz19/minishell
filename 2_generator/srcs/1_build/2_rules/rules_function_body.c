/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_function_body.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:41:21 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/04 16:41:22 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator_rules_priv.h"

static void	rules_build_function_body_1(t_rule *rules);
static void	rules_build_function_body_2(t_rule *rules);

/*
function_body    : compound_command               (apply rule 9)
                 | compound_command redirect_list (apply rule 9)
                 ;
*/
void	rules_build_function_body(t_rule *rules)
{
	rules_build_function_body_1(rules);
	rules_build_function_body_2(rules);
}

// function_body -> compound_command (apply rule 9)
static void	rules_build_function_body_1(t_rule *rules)
{
	rules[RULE_FUNCTION_BODY_1].lhs = SYM_function_body;
	rules[RULE_FUNCTION_BODY_1].rhs[0] = SYM_compound_command;
	rules[RULE_FUNCTION_BODY_1].rhs_len = 1;
}

// function_body -> compound_command redirect_list (apply rule 9)
static void	rules_build_function_body_2(t_rule *rules)
{
	rules[RULE_FUNCTION_BODY_2].lhs = SYM_function_body;
	rules[RULE_FUNCTION_BODY_2].rhs[0] = SYM_compound_command;
	rules[RULE_FUNCTION_BODY_2].rhs[1] = SYM_redirect_list;
	rules[RULE_FUNCTION_BODY_2].rhs_len = 2;
}
