/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:41:32 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/04 16:41:33 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator_rules_priv.h"

/*
in               : In (apply rule 6)
                 ;
*/
void	rules_build_in(t_rule *rules)
{
	rules[RULE_IN_1].lhs = SYM_in;
	rules[RULE_IN_1].rhs[0] = SYM_In;
	rules[RULE_IN_1].rhs_len = 1;
}
