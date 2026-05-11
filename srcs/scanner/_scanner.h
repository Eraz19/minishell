/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _scanner.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:11:57 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/11 13:42:50 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _SCANNER_H
# define _SCANNER_H

# include "types.h" 
# include "scanner.h"

typedef struct s_operator_args
{
	int				len;
	t_token_type	type;
	int				value;
}	t_operator_args;

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

bool		is_blank(t_lexer *lexer, size_t i);
t_token		*create_word_token(t_lexer *lexer, size_t i);
t_token		*create_operator_token(t_operator_args args, size_t i);

int			update_ctx_in_param(t_ctx_stack *ctx, char *input_ptr, size_t *i);
int			update_ctx_in_arithm(t_ctx_stack *ctx, char *input_ptr, size_t *i);
int			update_ctx_in_dquote(t_ctx_stack *ctx, char *input_ptr, size_t *i);
int			update_ctx_in_no_ctx(t_ctx_stack *ctx, char *input_ptr, size_t *i);
int			update_ctx_in_squote(t_ctx_stack *ctx, char *input_ptr, size_t *i);
int			update_ctx_in_backtick(t_ctx_stack *ctx, char *input_ptr,
				size_t *i);

bool		is_operator(t_lexer *lexer, t_operator_args *args, size_t i);

bool		is_semi(t_lexer *lexer, t_operator_args *args, size_t i);
bool		is_pipe(t_lexer *lexer, t_operator_args *args, size_t i);
bool		is_newline(t_lexer *lexer, t_operator_args *args, size_t i);
bool		is_ampersand(t_lexer *lexer, t_operator_args *args, size_t i);
bool		is_parenthesis(t_lexer *lexer, t_operator_args *args, size_t i);

bool		is_less(t_lexer *lexer, t_operator_args *args, size_t i);
bool		is_great(t_lexer *lexer, t_operator_args *args, size_t i);
bool		is_io_number(t_lexer *lexer, t_operator_args *args, size_t i);

bool		escape_char_in_backtick(size_t *i);
bool		escape_char_in_param(char *input_ptr, size_t *i);
bool		escape_char_in_arithm(char *input_ptr, size_t *i);
bool		escape_char_in_dquote(char *input_ptr, size_t *i);
bool		escape_char_in_no_ctx(char *input_ptr, size_t *i);

// ---------- DEBUG ----------

char		*DEBUG_token_type_stringify(t_token_type type);

#endif
