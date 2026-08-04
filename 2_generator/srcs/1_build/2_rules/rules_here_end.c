/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_here_end.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:41:26 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/04 16:41:27 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator_rules_priv.h"

/*
here_end         : WORD (apply rule 3)
                 ;
*/
void	rules_build_here_end(t_rule *rules)
{
	rules[RULE_HERE_END_1].lhs = SYM_here_end;
	rules[RULE_HERE_END_1].rhs[0] = SYM_WORD;
	rules[RULE_HERE_END_1].rhs_len = 1;
}
