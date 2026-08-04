/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_function_definition.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:41:24 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/04 16:41:25 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator_rules_priv.h"

/*
Original rule:
function_definition : fname '(' ')' linebreak function_body
                    ;
*/
void	rules_build_function_definition(t_rule *rules)
{
	rules[RULE_FUNCTION_DEFINITION_1].lhs = SYM_function_definition;
	rules[RULE_FUNCTION_DEFINITION_1].rhs[0] = SYM_fname;
	rules[RULE_FUNCTION_DEFINITION_1].rhs[1] = SYM_LPARENTHESIS;
	rules[RULE_FUNCTION_DEFINITION_1].rhs[2] = SYM_RPARENTHESIS;
	rules[RULE_FUNCTION_DEFINITION_1].rhs[3] = SYM_linebreak;
	rules[RULE_FUNCTION_DEFINITION_1].rhs[4] = SYM_function_body;
	rules[RULE_FUNCTION_DEFINITION_1].rhs_len = 5;
}
