/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_qualifiers.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 14:50:46 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/04 14:50:47 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAMMAR_QUALIFIERS_H
# define GRAMMAR_QUALIFIERS_H

# include "grammar_symbols.h"
# include <stdbool.h>
# include <sys/types.h>

/*
token_value is left unchanged after qualifier has been processed.
However, const can not be used because token_value can be temporary updated.
*/
typedef void	(*t_qualifier)(
					char *token_value,
					ssize_t assignment_offset,
					t_symbol *out_symbol);

void			qualify_word(
					char *token_value,
					ssize_t assignment_offset,
					t_symbol *out_symbol);
void			qualify_1(
					char *token_value,
					ssize_t assignment_offset,
					t_symbol *out_symbol);
void			qualify_2(
					char *token_value,
					ssize_t assignment_offset,
					t_symbol *out_symbol);
void			qualify_4(
					char *token_value,
					ssize_t assignment_offset,
					t_symbol *out_symbol);
void			qualify_5(
					char *token_value,
					ssize_t assignment_offset,
					t_symbol *out_symbol);
void			qualify_6a(
					char *token_value,
					ssize_t assignment_offset,
					t_symbol *out_symbol);
void			qualify_6b(
					char *token_value,
					ssize_t assignment_offset,
					t_symbol *out_symbol);
void			qualify_7a(
					char *token_value,
					ssize_t assignment_offset,
					t_symbol *out_symbol);
void			qualify_7b(
					char *token_value,
					ssize_t assignment_offset,
					t_symbol *out_symbol);

#endif
