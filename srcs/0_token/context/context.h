#ifndef CONTEXT_H
# define CONTEXT_H

# include <stdbool.h>
# include "context_stack.h" // IWYU pragma: keep
# include "context_stack_item.h"

/* ************************************************************************* */
/*                                QUOTING                                    */
/* ************************************************************************* */

bool	is_context_squote_start(char *str);
bool	is_context_dquote_start(char *str);
bool	is_context_dollar_squote_start(char *str);
bool	is_quoting_context_start(char *str, t_context *context);

bool	is_context_quoting(t_context context);

bool	is_in_context_dquote_whitelist(char c);
bool	is_in_context_squote_whitelist(char c);
bool	is_in_context_dollar_squote_whitelist(char c);
bool	is_in_quoting_whitelist(char c, t_context context);

bool	is_context_dquote_ending(char c, void *_);
bool	is_context_squote_ending(char c, void *_);
bool	is_quoting_ending(char c, t_context context);
bool	is_context_dollar_squote_ending(char c, void *_);

/* ************************************************************************* */
/*                                EXPANSION                                  */
/* ************************************************************************* */

bool	is_context_param_start(char *str);
bool	is_context_arith_start(char *str);
bool	is_context_cmd_sub_start(char *str);
bool	is_context_backtick_start(char *str);
bool	is_expansion_context_start(char *str, t_context *context);


bool	is_in_context_param_whitelist(char c);
bool	is_in_context_backtick_whitelist(char c);
bool	is_in_context_backtick_special_whitelist(char c);
bool	is_in_expansion_whitelist(char c, t_context context);

bool	is_context_param_ending(char c, void *_);
bool	is_context_backtick_ending(char c, void *_);
bool	is_context_arith_ending(char c, void *nesting_depth);

/* ************************************************************************* */
/*                                NONE                                       */
/* ************************************************************************* */

bool	is_blank(char c);

bool	is_in_context_none_whitelist(char c);

bool	is_context_none_ending(char c, void *_);

/* ************************************************************************* */
/*                                HEREDOC                                    */
/* ************************************************************************* */

bool	is_in_context_heredoc_whitelist(char c);

#endif
