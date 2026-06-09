/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __lexer_context.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 14:49:13 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/07 10:30:39 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __LEXER_CONTEXT_H
# define __LEXER_CONTEXT_H

# include "__lexer.h"

typedef struct s_escape_args
{
	bool	enable_line_continuation;
	bool	(*is_in_whitelist)(char);
	bool	(*is_in_special_whitelist)(char);
	bool	(*is_in_special_context)(t_lexer *);
}	t_escape_args;
	
typedef struct s_unescape_args
{
	void	*special_args;
	t_error	(*special_handler)(t_lexer *, void *);
}	t_unescape_args;

typedef struct s_context_args
{
	t_context		context;
	size_t			opening_len;
	void			*unescaped_args;
	t_error			(*escape)(t_lexer *);
	bool			(*is_end)(char, void *);
	t_error			(*unescaped)(t_lexer *, void *);
	t_error			(*quoting)(t_lexer *, t_context);
	bool			(*is_quoting)(char *, t_context *);
	t_error			(*expansion)(t_lexer *, t_context);
	bool			(*is_expansion)(char *, t_context *);
}	t_context_args;

t_error	context_scan(t_lexer *state, t_context_args args);
t_error	context_escape(t_lexer *state, t_escape_args args);
t_error	context_unescape(t_lexer *state, t_unescape_args args);

t_error	context_param(t_lexer *state);
t_error	context_arith(t_lexer *state);
t_error	context_dquote(t_lexer *state);
t_error	context_squote(t_lexer *state);
t_error	context_backtick(t_lexer *state);
t_error	context_dollar_squote(t_lexer *state);

#endif
