/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 10:24:03 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 18:02:48 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER__H
# define LEXER__H

# include "token.h"
# include "error.h"
# include "context.h"
# include "input_stack_.h"

typedef struct s_lexer_backup
{
    size_t          i;
    t_token_type    token_type;
    size_t          context_len;
    size_t          token_value_len;
}   t_lexer_backup;

typedef struct s_lexer
{
	t_error				err;
	t_input_stack_item	input;
	t_token				token;
	bool				is_tty;
	t_input_stack		input_stack;
	bool				reached_EOI;
	bool				emited_token;
}	t_lexer;

void			lexer_free(t_lexer *state);
void			lexer_init(t_lexer *state);
void			lexer_load(t_lexer *state, bool is_tty);

t_lexer_backup	lexer_backup(t_lexer *state);
void			lexer_advance(t_lexer *state, size_t offset);
t_error			lexer_delimit_token(t_lexer *state, t_token *token);
t_error			lexer_restore(t_lexer *state, t_lexer_backup backup);
t_error			lexer_consume(t_lexer *state, t_token_type type, size_t iter);

bool			is_operator_char(t_lexer *state);
t_error			lexer_add_char_into_token_operator(t_lexer *state);

t_error			lexer_context(t_lexer *state, t_context context);

t_error			lexer_rules(t_lexer *state, t_token *token, t_context *context);

#endif
