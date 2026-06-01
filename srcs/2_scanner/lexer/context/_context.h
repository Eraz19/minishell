/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _context.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 14:49:13 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/01 11:13:47 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CONTEXT_H
# define _CONTEXT_H

# include "../_lexer.h"

typedef struct s_escape_handler
{
	bool	enable_line_continuation;
	bool	(*is_in_whitelist)(char);
	bool	(*is_in_special_whitelist)(char);
	bool	(*is_in_special_context)(t_lexer *);
}	t_escape_handler;

typedef struct s_unescape_handler
{
	void	*special_args;
	bool	(*special_handler)(t_lexer *, void *);
}	t_unescape_handler;

typedef struct s_ctx_handler
{
	t_scanner_ctx	ctx_mode;
	size_t			opening_len;
	void			*unescaped_args;
	bool			(*is_end)(char);
	bool			(*escape)(t_lexer *);
	bool			(*quoting)(t_lexer *);
	bool			(*substitution)(t_lexer *);
	bool			(*unescaped)(t_lexer *, void *);
}	t_ctx_handler;

bool			is_ctx_param_ending(char c);
bool			is_ctx_squote_ending(char c);
bool			is_ctx_dquote_ending(char c);
bool			is_ctx_backtick_ending(char c);
bool			is_ctx_dollar_squote_ending(char c);

bool			is_in_ctx_none_whitelist(char c);
bool			is_in_ctx_param_whitelist(char c);
bool			is_in_ctx_dquote_whitelist(char c);
bool			is_in_ctx_squote_whitelist(char c);
bool			is_in_ctx_backtick_whitelist(char c);
bool			is_in_ctx_dollar_squote_whitelist(char c);
bool			is_in_ctx_backtick_special_whitelist(char c);

t_ctx_handler	ctx_param_rules(void);
t_ctx_handler	ctx_squote_rules(void);
t_ctx_handler	ctx_dquote_rules(void);
t_ctx_handler	ctx_backtick_rules(void);
t_ctx_handler	ctx_dollar_squote_rules(void);
t_ctx_handler	ctx_arith_rules(size_t *nesting_depth);

bool			ctx_arith(t_lexer *state);
bool			ctx_handle(t_lexer *state, t_ctx_handler args);
bool			ctx_escape(t_lexer *state, t_escape_handler args);
bool			ctx_unescape(t_lexer *state, t_unescape_handler args);
bool			ctx_start(t_lexer *state, t_scanner_ctx ctx, size_t len);
void			ctx_escape_next_char(t_lexer *state, t_escape_handler args);

#endif
