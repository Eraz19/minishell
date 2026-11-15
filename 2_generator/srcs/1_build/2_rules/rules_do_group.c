/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_do_group.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:41:05 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/04 16:41:06 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator_rules_priv.h"

/*
do_group         : Do compound_list Done (apply rule 6)
                 ;
*/
void	rules_build_do_group(t_rule *rules)
{
	rules[RULE_DO_GROUP_1].lhs = SYM_do_group;
	rules[RULE_DO_GROUP_1].rhs[0] = SYM_Do;
	rules[RULE_DO_GROUP_1].rhs[1] = SYM_compound_list;
	rules[RULE_DO_GROUP_1].rhs[2] = SYM_Done;
	rules[RULE_DO_GROUP_1].rhs_len = 3;
}
