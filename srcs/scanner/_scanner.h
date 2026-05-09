/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _scanner.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:11:57 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/09 16:15:59 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _SCANNER_H
# define _SCANNER_H

# include "types.h" 
# include "scanner.h"

char		*read_tty(void);
bool		complete_tty(char **prev_line);
char		*read_script(t_file_path script);

bool		lex_line(t_token **res, t_lexer *lexer);

t_lexer_ctx	ctx_pop(t_ctx_stack *stack);
t_lexer_ctx	ctx_view(t_ctx_stack *stack);
bool		ctx_update_nesting(t_ctx_stack *stack, int value);
bool		ctx_push(t_ctx_stack *stack, t_lexer_ctx_type ctx);

void		free_token(t_token **token_ptr);
t_token		*create_token(char *content, size_t offset, t_token_type type);

bool		is_blank_end_token(char *input_ptr);
t_token		*end_token_by_blank(char *input_ptr, size_t start, size_t i);
t_token		*end_token_by_operator(t_token_type type, int io_number, size_t i);

bool		update_ctx_in_param(t_ctx_stack *ctx, char *input_ptr, size_t *i);
bool		update_ctx_in_arithm(t_ctx_stack *ctx, char *input_ptr, size_t *i);
bool		update_ctx_in_dquote(t_ctx_stack *ctx, char *input_ptr, size_t *i);
bool		update_ctx_in_no_ctx(t_ctx_stack *ctx, char *input_ptr, size_t *i);
bool		update_ctx_in_squote(t_ctx_stack *ctx, char *input_ptr, size_t *i);
bool		update_ctx_in_backtick(t_ctx_stack *ctx, char *input_ptr,
				size_t *i);

bool		is_operator(t_token_type *type, int *value, char *input_ptr);

bool		is_semi_operator(t_token_type *type, char *input_ptr);
bool		is_pipe_operator(t_token_type *type, char *input_ptr);
bool		is_newline_operator(t_token_type *type, char *input_ptr);
bool		is_ampersand_operator(t_token_type *type, char *input_ptr);
bool		is_parenthesis_operator(t_token_type *type, char *input_ptr);

bool		is_less_operator(t_token_type *type, char *input_ptr);
bool		is_great_operator(t_token_type *type, char *input_ptr);
bool		is_io_number_operator(t_token_type *type, int *value,
				char * input_ptr);

bool		escape_char_in_backtick(size_t *i);
bool		escape_char_in_param(char *input_ptr, size_t *i);
bool		escape_char_in_arithm(char *input_ptr, size_t *i);
bool		escape_char_in_dquote(char *input_ptr, size_t *i);
bool		escape_char_in_no_ctx(char *input_ptr, size_t *i);

// ---------- DEBUG ----------

char		*DEBUG_token_type_stringify(t_token_type type);

#endif
