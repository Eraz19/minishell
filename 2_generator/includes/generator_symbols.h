/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator_symbols.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:39:04 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/04 16:39:06 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERATOR_SYMBOLS_H
# define GENERATOR_SYMBOLS_H

# include "grammar_symbols.h"
# include "grammar_rules.h"
# include <stdbool.h>
# include <stddef.h>

void	symbols_build_nullables_table(
			const t_rule rules[RULE_COUNT],
			bool nullable_symbols[SYM_COUNT]);

#endif
