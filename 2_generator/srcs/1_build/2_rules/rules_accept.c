/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_accept.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:40:13 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/04 16:40:14 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator_rules_priv.h"

/*
⚠️ Custom rule (bash-like cmd sub parsing hack)
accept           : start
                 ;
*/
void	rules_build_accept(t_rule *rules)
{
	rules[RULE_ACCEPT].lhs = SYM_accept;
	rules[RULE_ACCEPT].rhs[0] = SYM_start;
	rules[RULE_ACCEPT].rhs_len = 1;
}
