# include "context.h"
# include "heredoc_body_.h"

typedef struct s_heredoc_body_context_args
{
	t_context					context;
	size_t						opening_len;
	size_t						closing_len;
	t_context_parser_stack_item	*stack_item;
	void						*unescaped_args;
	t_error						(*escape)(t_heredoc_body *);
	bool						(*is_end)(char, void *);
	t_error						(*unescaped)(t_heredoc_body *, void *);
	t_error						(*quoting)(t_heredoc_body *, t_context);
	bool						(*is_quoting)(char *, t_context *);
	t_error						(*expansion)(t_heredoc_body *, t_context);
	bool						(*is_expansion)(char *, t_context *);
}	t_heredoc_body_context_args;

t_error	heredoc_body_rule_expansion(t_heredoc_body *state, t_context context)
{
	if (context != CONTEXT_ARITH)
		return (lexer_context(state, context));
	else
	{
		if (lexer_context(state, CONTEXT_ARITH).type == ERR_CTX_END_NOT_FOUND)
		{
			state->err = error(ERR_NO);
			return (lexer_context(state, CONTEXT_CMD_SUB));
		}
		return (state->err);
	}
}

static bool	is_heredoc_end(t_heredoc_body *state, void *args)
{
	(void)args;
	return (state->i >= state->content.len);
}

static t_error	context_heredoc_escape(t_heredoc_body *state)
{
	t_escape_args	args;

	args.is_in_special_context = NULL;
	args.is_in_special_whitelist = NULL;
	args.enable_line_continuation = true;
	args.is_in_whitelist = is_in_context_dquote_whitelist;
	return (lexer_context_escape(state, args));
}

static t_error	context_heredoc_unescape(t_heredoc_body *state, void *_)
{
	t_unescape_args	args;

	args.special_args = NULL;
	args.special_handler = NULL;
	return (lexer_context_unescape(state, args));
}






static t_error	heredoc_body_context_start(
	t_heredoc_body *state,
	t_heredoc_body_context_args args)
{
	if (args.stack_item != NULL)
		args.stack_item->start = state->i;
	state->err = context_stack_push(&state->contexts, args.stack_item);
	if (state->err.type)
		return (state->err);
	return (state->i++, state->err);
}

static t_error	heredoc_body_context_end(t_heredoc_body *state)
{
	t_context_parser_stack_item	*item;

	state->err = context_stack_bpop(&state->contexts, &item);
	if (state->err.type)
		return (state->err);
	return (item->end = state->i, state->err);
}

t_error	heredoc_body_context_unescape(t_lexer *state, t_unescape_args args)
{
	if (state->input->str[state->input->i] == '\0')
		return (context_EOI(state));
	else if (args.special_handler != NULL)
		return (args.special_handler(state, args.special_args));
	else
		return (lexer_consume(state, state->token->type, 1));
}

t_error	heredoc_body_context_escape(t_heredoc_body *state, t_escape_args args)
{
	state->token->type = TOKEN_TOKEN;
	if (args.enable_line_continuation &&
		state->input->str[state->input->i + 1] == '\n')
	{
		lexer_advance(state, 2);
		if (state->input->str[state->input->i] == '\0')
			return (context_EOI(state));
	}
	else if (state->input->str[state->input->i] == '\0')
		return (context_EOI(state));
	else
	{
		if (lexer_consume(state, state->token->type, 1).type)
			return (state->err);	
		if (context_escape_next_char(state, args).type)
			return (state->err);
	}
	return (state->err);
}

t_error	heredoc_body_context_scan(
	t_heredoc_body *state,
	t_heredoc_body_context_args args)
{
	char		*str;
	t_context	context;

	if (heredoc_body_context_start(state, args).type)
		return (state->err);
	while (true)
	{
		if (state->err.type)
			return (state->err);
		str = state->input->str + state->input->i;
		if (args.is_end != NULL && args.is_end(*str, args.unescaped_args))
			return (heredoc_body_context_end(state));
		else if (*str == '\\')
			args.escape(state);
		else if (args.quoting != NULL && args.is_quoting(str, &context))
			args.quoting(state, context);
		else if (args.expansion != NULL && args.is_expansion(str, &context))
			args.expansion(state, context);
		else
			args.unescaped(state, args.unescaped_args);
	}
}


static t_heredoc_body_context_args	context_heredoc_body_rules(void)
{
	t_heredoc_body_context_args	res;

	res.quoting = NULL;
	res.opening_len = 0;
	res.closing_len = 0;
	res.stack_item = NULL;
	res.is_quoting = NULL;
	res.unescaped_args = NULL;
	res.context = CONTEXT_NONE;
	res.is_end = is_heredoc_end;
	res.escape = context_heredoc_escape;
	res.unescaped = context_heredoc_unescape;
	res.is_expansion = is_expansion_context;
	res.expansion = heredoc_body_rule_expansion;
	return (res);
}


t_error	heredoc_track_body_context(t_buff *body, t_context_stack *stack)
{
	t_heredoc_body	state;

	heredoc_body_init(&state);
	if (!buff_append(&state.content, body->data, (long)body->len))
		return (state.err = error_sys(), heredoc_body_free(&state), state.err);
	if (heredoc_body_context_scan(&state, context_heredoc_body_rules(item)).type)
		return (state.err);
}
