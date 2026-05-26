/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _context.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 16:01:20 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/19 10:23:51 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CONTEXT_H
# define _CONTEXT_H

# include <stdbool.h>
# include "../_lexer.h"

typedef struct s_ctx_update_maybe
{
	t_error	err;
	bool	res;
}	t_ctx_update_maybe;

bool	on_ctx_update_failure(t_ctx_update_maybe *res, t_error err);
bool	on_ctx_update_success(t_ctx_update_maybe *res, bool is_updated);

bool	is_squote_start(t_lexer *lexer);
bool	squote(t_ctx_update_maybe *res, t_lexer *lexer);
bool	squote_end(t_ctx_update_maybe *res, t_lexer *lexer);
bool	squote_body(t_ctx_update_maybe *res, t_lexer *lexer);
bool	squote_start(t_ctx_update_maybe *res, t_lexer *lexer);
bool	backslash_in_squote(t_ctx_update_maybe *res, t_lexer *lexer);

bool	is_dquote_start(t_lexer *lexer);
bool	dquote(t_ctx_update_maybe *res, t_lexer *lexer);
bool	dquote_end(t_ctx_update_maybe *res, t_lexer *lexer);
bool	dquote_body(t_ctx_update_maybe *res, t_lexer *lexer);
bool	dquote_start(t_ctx_update_maybe *res, t_lexer *lexer);
bool	backslash_in_dquote(t_ctx_update_maybe *res, t_lexer *lexer);

bool	is_cmd_sub_start(t_lexer *lexer);
bool	cmd_sub(t_ctx_update_maybe *res, t_lexer *lexer);
bool	cmd_sub_end(t_ctx_update_maybe *res, t_lexer *lexer);
bool	cmd_sub_body(t_ctx_update_maybe *res, t_lexer *lexer);
bool	cmd_sub_start(t_ctx_update_maybe *res, t_lexer *lexer);
bool	backslash_in_cmd_sub(t_ctx_update_maybe *res, t_lexer *lexer);

bool	is_param_start(t_lexer *lexer);
bool	param(t_ctx_update_maybe *res, t_lexer *lexer);
bool	param_end(t_ctx_update_maybe *res, t_lexer *lexer);
bool	param_body(t_ctx_update_maybe *res, t_lexer *lexer);
bool	param_start(t_ctx_update_maybe *res, t_lexer *lexer);
bool	backslash_in_param(t_ctx_update_maybe *res, t_lexer *lexer);

bool	is_arith_start(t_lexer *lexer);
bool	arith(t_ctx_update_maybe *res, t_lexer *lexer);
bool	arith_end(t_ctx_update_maybe *res, t_lexer *lexer);
bool	arith_body(t_ctx_update_maybe *res, t_lexer *lexer);
bool	arith_start(t_ctx_update_maybe *res, t_lexer *lexer);
bool	backslash_in_arith(t_ctx_update_maybe *res, t_lexer *lexer);

bool	is_backtick_start(t_lexer *lexer);
bool	backtick(t_ctx_update_maybe *res, t_lexer *lexer);
bool	backtick_end(t_ctx_update_maybe *res, t_lexer *lexer);
bool	backtick_body(t_ctx_update_maybe *res, t_lexer *lexer);
bool	backtick_start(t_ctx_update_maybe *res, t_lexer *lexer);
bool	backslash_in_backtick(t_ctx_update_maybe *res, t_lexer *lexer);

bool	is_comment_start(t_lexer *lexer);
bool	comment(t_ctx_update_maybe *res, t_lexer *lexer);
bool	comment_end(t_ctx_update_maybe *res, t_lexer *lexer);
bool	comment_body(t_ctx_update_maybe *res, t_lexer *lexer);
bool	comment_start(t_ctx_update_maybe *res, t_lexer *lexer);
bool	backslash_in_comment(t_ctx_update_maybe *res, t_lexer *lexer);

char	*DEBUG_ctx_type_stringify(t_lexer_ctx_type type);

#endif
