#ifndef BODY__H
# define BODY__H

# include "lexer.h"
# include "heredoc.h"
# include "context.h"

typedef struct s_body
{
	size_t			i;
	t_error			err;
	t_heredoc_item	*item;
	t_string		line;
	t_string		content;
	t_context_stack	contexts;
}	t_body;

void					body_init(t_body *body);
void					body_free(t_body *body);
void					body_load(t_body *body, t_heredoc_item *item);

// ============= MAIN FUNCTIONS ================

t_lexer_context_args	body_context_rules(void);
t_error					read_body_file(t_string *out, const t_string *path);
t_error					save_body_in_file(const t_string *path, t_string *body);

// ============= INPUT SCAN FUNCTIONS ================

bool					is_line_delimiter(t_body *body);
t_error					get_body_content(t_body *body);
t_error					get_body_line(t_body *body, char *EOL, size_t *i);
t_error					body_continuation(t_body *body, bool *continuation);

// ============= LEXER RULES FUNCTIONS ================

t_error					body_escape(t_lexer *lexer);
t_error					body_unescape(t_lexer *lexer, void *_);

#endif
