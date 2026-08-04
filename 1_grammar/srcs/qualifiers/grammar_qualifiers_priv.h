/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_qualifiers_priv.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 14:51:35 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/04 14:51:36 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAMMAR_QUALIFIERS_PRIV_H
# define GRAMMAR_QUALIFIERS_PRIV_H

# include "grammar_symbols.h"
# include <stdbool.h>
# include <sys/types.h>

bool	qualify_try_reserved_word(
			char *token_value,
			ssize_t assignment_offset,
			t_symbol *out_symbol);
bool	qualify_try_name(
			char *token_value,
			ssize_t assignment_offset,
			t_symbol *out_symbol);

#endif
