#ifndef CONTEXT_H
# define CONTEXT_H

# include "error.h"
# include "libft.h"

typedef t_vector	t_context_stack;

typedef enum e_context
{
	CONTEXT_NONE,			/**< Top level, outside any quoting or expansion. */
	CONTEXT_SQUOTE,			/**< Single quotes: '...'. */
	CONTEXT_DQUOTE,			/**< Double quotes: "...". */
	CONTEXT_DOLLAR_SQUOTE,	/**< ANSI-C quoting: $'...'. */
	CONTEXT_BACKTICK,		/**< Backquote command substitution: `...`. */
	CONTEXT_CMD_SUB,		/**< Command substitution: $(...). */
	CONTEXT_ARITH,			/**< Arithmetic expansion: $((...)). */
	CONTEXT_PARAM,			/**< Parameter expansion: ${...}. */
	CONTEXT_HEREDOC,		/**< Here-document body: double-quote-like, but
								 the '"' character stays literal. */
}	t_context;

typedef struct s_context_stack_item
{
	size_t		end;
	size_t		start;
	t_context	context;
}	t_context_stack_item;

void	context_stack_init(t_context_stack *stack);
void	context_stack_free(t_context_stack *stack);
t_error	context_stack_item_init(t_context_stack_item **item, t_context context);

// ============= CONTEXT STACK MAIN FUNCTIONS ================

t_error	context_stack_dup(t_context_stack *dst, const t_context_stack *src);
t_error	context_stack_push(t_context_stack *stack, t_context_stack_item *item);
t_error	context_stack_bpop(t_context_stack *stack, t_context_stack_item **item);
t_error	context_stack_fpop(t_context_stack *stack, t_context_stack_item **item);
t_error	context_stack_get(
			const t_context_stack *stack,
			t_context_stack_item **item,
			size_t index);

// ============= SUBSTITUTION CONTEXT FUNCTIONS ================

bool	is_substitution_context(char *str, t_context *context);
bool	is_in_substitution_whitelist(char c, t_context context);

bool	is_context_arith_start(char *str);
bool	is_context_arith_ending(char c, void *nesting_depth);

bool	is_context_backtick_start(char *str);
bool	is_in_context_backtick_whitelist(char c);
bool	is_in_context_backtick_special_whitelist(char c);
bool	is_context_backtick_ending(char c, void *_);

bool	is_context_param_start(char *str);
bool	is_in_context_param_whitelist(char c);
bool	is_context_param_ending(char c, void *_);

bool	is_context_cmd_sub_start(char *str);

// ============= NONE CONTEXT FUNCTIONS ================

bool	is_blank(char c);
bool	is_in_context_none_whitelist(char c);
bool	is_context_none_ending(char c, void *_);

// ============= QUOTING CONTEXT FUNCTIONS ================

bool	is_context_quoting(t_context context);
bool	is_quoting_ending(char c, t_context context);
bool	is_quoting_context(char *str, t_context *context);
bool	is_in_quoting_whitelist(char c, t_context context);

bool	is_context_dollar_squote_start(char *str);
bool	is_in_context_dollar_squote_whitelist(char c);
bool	is_context_dollar_squote_ending(char c, void *_);

bool	is_context_dquote_start(char *str);
bool	is_in_context_dquote_whitelist(char c);
bool	is_context_dquote_ending(char c, void *_);

bool	is_in_context_heredoc_whitelist(char c);
bool	is_context_heredoc_ending(char c, void *_);

bool	is_context_squote_start(char *str);
bool	is_in_context_squote_whitelist(char c);
bool	is_context_squote_ending(char c, void *_);

#endif
