#include "debug.h"
#include "symbols_type.h"
#include "action_type.h"
#include "token.h"
#include "lr_machine_type.h"
#include "lr_state_type.h"
#include "rule_state_type.h"
#include "parser_item_stack_type.h"
#include "cst_type.h"
#include "cmd.h"
#include "ast.h"
#include "heredoc.h"
#include "parser_priv.h"
#include "logs.h"
#include "lexer.h"
#include <stdio.h>
#include <stdbool.h>

/* ************************************************************************* */
/*                                 INSTANCE                                  */
/* ************************************************************************* */

void	dump_lexer_instance(t_lexer *lexer)
{
	fprintf(stderr, " ╰─────── LEXER   => [%p | inputs=%zu | input='%s' [%zu] | token='%s' (%s) | emitted=%s]\n",
		lexer,
		lexer->input_stack.len,
		lexer->input ? lexer->input->str.data : NULL,
		lexer->input ? lexer->input->i : 0,
		lexer->token ? lexer->token->value.data : NULL,
		lexer->token ? token_type_to_string(lexer->token->type) : NULL,
		bool_to_string(lexer->emited_token));
}

void	dump_scanner_instance(t_scanner *scanner)
{
	fprintf(stderr, " ├─────── SCANNER => [%p | mode=%s | source='%s' | parent=%p]\n",
		scanner, scan_mode_to_string(scanner->mode), scanner->source, scanner->parent_scanner);
}

void	dump_parser_instance(t_parser *parser)
{
	fprintf(stderr, " ├─────── PARSER  => [%p | lookahead='%s'->'%s' | tokens=%zu | items=%zu | here=%zu | cst=%p | search=%s | end_i=%ld]\n",
		parser, symbol_to_string(parser->lookahead_symbol), symbol_to_string(parser->lookahead_raw_symbol),
		parser->token_pool.len, parser->item_stack.len, parser->here_stack.len,
		parser->cst, bool_to_string(parser->search_cmd_sub_end), parser->cmd_sub_end_index);
}

void	dump_runner_instance(t_runner *runner)
{
	fprintf(stderr, " ├─────── RUNNER  => [%p | loop_depth=%zu | control_depth=%zu | parent=%p | child=%p]\n",
		runner, runner->loop_depth, runner->control_depth, runner->parent, runner->child);
}

void	dump_shell_instance(t_runner *runner, const char *caller)
{
	fprintf(stderr, YELLOW "[SHELL ] new instance from %s():\n", caller);
	dump_runner_instance(runner);
	dump_parser_instance(&runner->parser);
	dump_scanner_instance(&runner->parser.scanner);
	dump_lexer_instance(&runner->parser.scanner.lexer);
	fprintf(stderr, NC);
}

/* ************************************************************************* */
/*                                   BOOL                                    */
/* ************************************************************************* */

const char	*bool_to_string(bool value)
{
	if (value)
		return ("true");
	return ("false");
}

const char	*cmd_type_to_string(t_cmd_type type)
{
	switch (type)
	{
		case CMD_NONE: return ("CMD_NONE");
		case CMD_SPECIAL_BUILTIN: return ("CMD_SPECIAL_BUILTIN");
		case CMD_FUNCTION: return ("CMD_FUNCTION");
		case CMD_BUILTIN: return ("CMD_BUILTIN");
		case CMD_EXTERNAL: return ("CMD_EXTERNAL");
		default: return ("unknown");
	}
}

const char	*scan_mode_to_string(t_scan_mode mode)
{
	switch (mode)
	{
		case SCAN_MODE_NONE: return ("SCAN_MODE_NONE");
		case SCAN_MODE_AUTO: return ("SCAN_MODE_AUTO");
		case SCAN_MODE_FILE: return ("SCAN_MODE_FILE");
		case SCAN_MODE_CMD_SUB: return ("SCAN_MODE_CMD_SUB");
		case SCAN_MODE_STDIN: return ("SCAN_MODE_STDIN");
		case SCAN_MODE_STRING: return ("SCAN_MODE_STRING");
		case SCAN_MODE_STRING_AND_CONTINUE: return ("SCAN_MODE_STRING_AND_CONTINUE");
		default: return ("unknown");
	}
}

#if defined DEBUG_CST || defined DEBUG_AST
static void	dump_string_value(const t_string *value)
{
	size_t	i;
	char	c;

	fprintf(stderr, "\"");
	if (value == NULL || value->data == NULL)
		return ((void)fprintf(stderr, "\""));
	i = 0;
	while (i < value->len)
	{
		c = value->data[i];
		if (c == '\n')
			fprintf(stderr, "\\n");
		else if (c == '\t')
			fprintf(stderr, "\\t");
		else if (c == '\r')
			fprintf(stderr, "\\r");
		else if (c == '\\')
			fprintf(stderr, "\\\\");
		else if (c == '"')
			fprintf(stderr, "\\\"");
		else if (c >= 32 && c <= 126)
			fprintf(stderr, "%c", c);
		else
			fprintf(stderr, "\\x%02x", (unsigned char)c);
		i++;
	}
	fprintf(stderr, "\"");
}
#endif

/* ************************************************************************* */
/*                                   TOKEN                                   */
/* ************************************************************************* */

const char	*token_type_to_string(t_token_type token_type)
{
	char	*formatted;

	switch (token_type)
	{
		case TOKEN_NONE: return ("NONE");
		case TOKEN_DOLPAREN: return ("DOLPAREN");
		case TOKEN_TOKEN: return ("TOKEN");
		case TOKEN_NEWLINE: return ("NEWLINE");
		case TOKEN_SCOLON: return ("SCOLON");
		case TOKEN_AMPERSAND: return ("AMPERSAND");
		case TOKEN_DSEMI: return ("DSEMI");
		case TOKEN_SEMI_AND: return ("SEMI_AND");
		case TOKEN_AND_IF: return ("AND_IF");
		case TOKEN_OR_IF: return ("OR_IF");
		case TOKEN_PIPE: return ("PIPE");
		case TOKEN_LPARENTHESIS: return ("LPARENTHESIS");
		case TOKEN_RPARENTHESIS: return ("RPARENTHESIS");
		case TOKEN_LESSAND: return ("LESSAND");
		case TOKEN_GREATAND: return ("GREATAND");
		case TOKEN_LESS: return ("LESS");
		case TOKEN_GREAT: return ("GREAT");
		case TOKEN_CLOBBER: return ("CLOBBER");
		case TOKEN_LESSGREAT: return ("LESSGREAT");
		case TOKEN_DGREAT: return ("DGREAT");
		case TOKEN_DLESS: return ("DLESS");
		case TOKEN_DLESSDASH: return ("DLESSDASH");
		case TOKEN_IO_NUMBER: return ("IO_NUMBER");
		case TOKEN_IO_LOCATION: return ("IO_LOCATION");
		case TOKEN_EOF: return ("EOF");
		default: return (asprintf(&formatted, "unknown (%i)", (int)token_type), formatted);
	}
}

/* ************************************************************************* */
/*                                  SYMBOL                                   */
/* ************************************************************************* */

const char	*symbol_to_string(t_symbol symbol)
{
	switch (symbol)
	{
		case SYM_accept: return ("SYM_accept");
		case SYM_start: return ("SYM_start");
		case SYM_cmd_sub: return ("SYM_cmd_sub");
		case SYM_DOLPAREN: return ("SYM_DOLPAREN");
		case SYM_TOKEN: return ("SYM_TOKEN");
		case SYM_WORD: return ("SYM_WORD");
		case SYM_NAME: return ("SYM_NAME");
		case SYM_ASSIGNMENT_WORD: return ("SYM_ASSIGNMENT_WORD");
		case SYM_NEWLINE: return ("SYM_NEWLINE");
		case SYM_SEMI: return ("SYM_SEMI");
		case SYM_DSEMI: return ("SYM_DSEMI");
		case SYM_SEMI_AND: return ("SYM_SEMI_AND");
		case SYM_AMPERSAND: return ("SYM_AMPERSAND");
		case SYM_AND_IF: return ("SYM_AND_IF");
		case SYM_OR_IF: return ("SYM_OR_IF");
		case SYM_PIPE: return ("SYM_PIPE");
		case SYM_LPARENTHESIS: return ("SYM_LPARENTHESIS");
		case SYM_RPARENTHESIS: return ("SYM_RPARENTHESIS");
		case SYM_IO_NUMBER: return ("SYM_IO_NUMBER");
		case SYM_IO_LOCATION: return ("SYM_IO_LOCATION");
		case SYM_LESS: return ("SYM_LESS");
		case SYM_DLESS: return ("SYM_DLESS");
		case SYM_DLESSDASH: return ("SYM_DLESSDASH");
		case SYM_LESSAND: return ("SYM_LESSAND");
		case SYM_GREAT: return ("SYM_GREAT");
		case SYM_DGREAT: return ("SYM_DGREAT");
		case SYM_GREATAND: return ("SYM_GREATAND");
		case SYM_CLOBBER: return ("SYM_CLOBBER");
		case SYM_LESSGREAT: return ("SYM_LESSGREAT");
		case SYM_Bang: return ("SYM_Bang");
		case SYM_Lbrace: return ("SYM_Lbrace");
		case SYM_Rbrace: return ("SYM_Rbrace");
		case SYM_Case: return ("SYM_Case");
		case SYM_Esac: return ("SYM_Esac");
		case SYM_Do: return ("SYM_Do");
		case SYM_Done: return ("SYM_Done");
		case SYM_If: return ("SYM_If");
		case SYM_Then: return ("SYM_Then");
		case SYM_Elif: return ("SYM_Elif");
		case SYM_Else: return ("SYM_Else");
		case SYM_Fi: return ("SYM_Fi");
		case SYM_For: return ("SYM_For");
		case SYM_In: return ("SYM_In");
		case SYM_Until: return ("SYM_Until");
		case SYM_While: return ("SYM_While");
		case SYM_EOF: return ("SYM_EOF");
		case SYM_program: return ("SYM_program");
		case SYM_complete_commands: return ("SYM_complete_commands");
		case SYM_complete_command: return ("SYM_complete_command");
		case SYM_list: return ("SYM_list");
		case SYM_and_or: return ("SYM_and_or");
		case SYM_pipeline: return ("SYM_pipeline");
		case SYM_pipe_sequence: return ("SYM_pipe_sequence");
		case SYM_command: return ("SYM_command");
		case SYM_compound_command: return ("SYM_compound_command");
		case SYM_subshell: return ("SYM_subshell");
		case SYM_compound_list: return ("SYM_compound_list");
		case SYM_term: return ("SYM_term");
		case SYM_for_clause: return ("SYM_for_clause");
		case SYM_name: return ("SYM_name");
		case SYM_in: return ("SYM_in");
		case SYM_wordlist: return ("SYM_wordlist");
		case SYM_case_clause: return ("SYM_case_clause");
		case SYM_case_list_ns: return ("SYM_case_list_ns");
		case SYM_case_list: return ("SYM_case_list");
		case SYM_case_item_ns: return ("SYM_case_item_ns");
		case SYM_case_item: return ("SYM_case_item");
		case SYM_pattern_list: return ("SYM_pattern_list");
		case SYM_if_clause: return ("SYM_if_clause");
		case SYM_else_part: return ("SYM_else_part");
		case SYM_while_clause: return ("SYM_while_clause");
		case SYM_until_clause: return ("SYM_until_clause");
		case SYM_function_definition: return ("SYM_function_definition");
		case SYM_function_body: return ("SYM_function_body");
		case SYM_fname: return ("SYM_fname");
		case SYM_brace_group: return ("SYM_brace_group");
		case SYM_do_group: return ("SYM_do_group");
		case SYM_simple_command: return ("SYM_simple_command");
		case SYM_cmd_name: return ("SYM_cmd_name");
		case SYM_cmd_word: return ("SYM_cmd_word");
		case SYM_cmd_prefix: return ("SYM_cmd_prefix");
		case SYM_cmd_suffix: return ("SYM_cmd_suffix");
		case SYM_redirect_list: return ("SYM_redirect_list");
		case SYM_io_redirect: return ("SYM_io_redirect");
		case SYM_io_file: return ("SYM_io_file");
		case SYM_filename: return ("SYM_filename");
		case SYM_io_here: return ("SYM_io_here");
		case SYM_here_end: return ("SYM_here_end");
		case SYM_newline_list: return ("SYM_newline_list");
		case SYM_linebreak: return ("SYM_linebreak");
		case SYM_separator_op: return ("SYM_separator_op");
		case SYM_separator: return ("SYM_separator");
		case SYM_sequential_sep: return ("SYM_sequential_sep");
		case SYM_COUNT: return ("SYM_COUNT");
		case SYM_NONE: return ("SYM_NONE");
		case SYM_error: return ("SYM_error");
		default: return ("unknown");
	}
}

/* ************************************************************************* */
/*                                   RULE                                    */
/* ************************************************************************* */

void	dump_rule(t_lr_machine *machine, size_t rule_id)
{
	t_rule	*rule;
	size_t	i;

	rule = &machine->rules[rule_id];
	fprintf(stderr, "[RULE] %zu lhs=%s rhs=", rule_id, symbol_to_string(rule->lhs));
	i = 0;
	while (i < rule->rhs_len)
	{
		fprintf(stderr, "%s ", symbol_to_string(rule->rhs[i]));
		i++;
	}
	fprintf(stderr, "rhs_len=%zu hook=%p\n", rule->rhs_len, rule->hook);
}

/* ************************************************************************* */
/*                                 LR_STATE                                  */
/* ************************************************************************* */

void	dump_lr_state(t_lr_machine *machine, size_t lr_state_id)
{
	t_lr_state		*state;
	t_rule_state	*rule_state;
	t_rule			*rule;
	t_symbol		next;
	size_t			i;

	state = &((t_lr_state *)machine->lr_states.data)[lr_state_id];
	fprintf(stderr, "\n[STATE %zu]\n", lr_state_id);
	i = 0;
	while (i < state->len)
	{
		rule_state = &((t_rule_state *)state->data)[i];
		rule = &machine->rules[rule_state->rule_id];
		next = SYM_NONE;
		if (rule_state->pos < rule->rhs_len)
			next = rule->rhs[rule_state->pos];
		fprintf(stderr, "rule=%zu pos=%zu lhs=%s next=%s lookahead=%s\n",
			rule_state->rule_id,
			rule_state->pos,
			symbol_to_string(rule->lhs),
			symbol_to_string(next),
			symbol_to_string(rule_state->lookahead));
		i++;
	}
	fprintf(stderr, "action[Lbrace]=%s:%zu\n",
		action_type_to_string(machine->actions[lr_state_id][SYM_Lbrace].type),
		machine->actions[lr_state_id][SYM_Lbrace].payload);
	fprintf(stderr, "action[WORD]=%s:%zu\n",
		action_type_to_string(machine->actions[lr_state_id][SYM_WORD].type),
		machine->actions[lr_state_id][SYM_WORD].payload);
	fprintf(stderr, "action[NEWLINE]=%s:%zu\n",
		action_type_to_string(machine->actions[lr_state_id][SYM_NEWLINE].type),
		machine->actions[lr_state_id][SYM_NEWLINE].payload);
}

/* ************************************************************************* */
/*                                  ACTION                                   */
/* ************************************************************************* */

const char	*action_type_to_string(t_action_type action_type)
{
	switch (action_type)
	{
		case ACTION_SHIFT: return ("ACTION_SHIFT");
		case ACTION_REDUCE: return ("ACTION_REDUCE");
		case ACTION_ACCEPT: return ("ACTION_ACCEPT");
		case ACTION_ERROR: return ("ACTION_ERROR");
		default: return ("unknown");
	}
}

/* ************************************************************************* */
/*                             PARSER ITEM STACK                             */
/* ************************************************************************* */

void	dump_parser_item_stack(t_parser_item_stack *stack)
{
	t_parser_item	*items;
	t_parser_item	*item;
	const char		*branch;
	const char		*color;
	size_t			i;

	if (stack == NULL)
		return ((void)fprintf(stderr, "[PARSER STACK] (null)\n"));
	items = (t_parser_item *)stack->data;
	fprintf(stderr, "[PARSER] ITEM STACK len=%zu cap=%zu\n",
		stack->len, stack->cap);
	i = 0;
	while (i < stack->len)
	{
		item = &items[i];
		branch = " ├──";
		if (i + 1 == stack->len)
			branch = " ╰──";
		color = NC;
		if (item->symbol <= SYM_TERMINAL_MAX)
			color = RED;
		else if (item->symbol <= SYM_complete_command)
			color = GREEN;
		else if (item->symbol <= SYM_NON_TERMINAL_MAX)
			color = YELLOW;
		fprintf(stderr,
			"%s[%3zu] %s%s%s state=%zu tokens=",
			branch,
			i,
			color,
			symbol_to_string(item->symbol),
			NC,
			item->lr_state_id);
		if (item->tokens_count == 0)
			fprintf(stderr, "empty");
		else
			fprintf(stderr, "%zu-%zu (%zu)",
				item->tokens_start_id,
				item->tokens_start_id + item->tokens_count - 1,
				item->tokens_count);
		fprintf(stderr, " cst=%p\n", (void *)item->cst_node);
		i++;
	}
}

/* ************************************************************************* */
/*                              LEXER INPUT STACK                            */
/* ************************************************************************* */

static void	dump_lexer_input_stack_string(const t_string *value)
{
	size_t	i;
	char	c;

	fprintf(stderr, "\"");
	if (value == NULL || value->data == NULL)
		return ((void)fprintf(stderr, "\""));
	i = 0;
	while (i < value->len)
	{
		c = value->data[i];
		if (c == '\n')
			fprintf(stderr, "\\n");
		else if (c == '\t')
			fprintf(stderr, "\\t");
		else if (c == '\r')
			fprintf(stderr, "\\r");
		else if (c == '\\')
			fprintf(stderr, "\\\\");
		else if (c == '"')
			fprintf(stderr, "\\\"");
		else if (c >= 32 && c <= 126)
			fprintf(stderr, "%c", c);
		else
			fprintf(stderr, "\\x%02x", (unsigned char)c);
		i++;
	}
	fprintf(stderr, "\"");
}

void	dump_input_stack(t_lexer_input_stack *stack)
{
	t_lexer_input_stack_item	**items;
	t_lexer_input_stack_item	*item;
	const char				*branch;
	size_t					i;

	if (stack == NULL)
		return ((void)fprintf(stderr, "[LEXER INPUT STACK] (null)\n"));
	items = (t_lexer_input_stack_item **)stack->data;
	fprintf(stderr, "[LEXER] INPUT STACK len=%zu cap=%zu\n",
		stack->len, stack->cap);
	i = 0;
	while (i < stack->len)
	{
		item = items[i];
		branch = " ├──";
		if (i + 1 == stack->len)
			branch = " ╰──";
		fprintf(stderr, "%s[%3zu] item=%p", branch, i, (void *)item);
		if (item == NULL)
			fprintf(stderr, " (null)\n");
		else
		{
			fprintf(stderr, " i=%zu str={len=%zu cap=%zu data=",
				item->i, item->str.len, item->str.cap);
			dump_lexer_input_stack_string(&item->str);
			fprintf(stderr, "}\n");
		}
		i++;
	}
}

/* ************************************************************************* */
/*                                CONTEXT STACK                              */
/* ************************************************************************* */

static const char	*debug_context_to_string(t_context context)
{
	switch (context)
	{
		case CONTEXT_NONE: return ("CONTEXT_NONE");
		case CONTEXT_SQUOTE: return ("CONTEXT_SQUOTE");
		case CONTEXT_DQUOTE: return ("CONTEXT_DQUOTE");
		case CONTEXT_DOLLAR_SQUOTE: return ("CONTEXT_DOLLAR_SQUOTE");
		case CONTEXT_BACKTICK: return ("CONTEXT_BACKTICK");
		case CONTEXT_CMD_SUB: return ("CONTEXT_CMD_SUB");
		case CONTEXT_ARITH: return ("CONTEXT_ARITH");
		case CONTEXT_PARAM: return ("CONTEXT_PARAM");
		case CONTEXT_HEREDOC: return ("CONTEXT_HEREDOC");
		default: return ("unknown");
	}
}

void	dump_context_stack(t_context_stack *stack)
{
	t_context_stack_item	**items;
	t_context_stack_item	*item;
	const char			*branch;
	size_t				i;

	if (stack == NULL)
		return ((void)fprintf(stderr, "[CONTEXT STACK] (null)\n"));
	items = (t_context_stack_item **)stack->data;
	fprintf(stderr, "[CONTEXT] STACK len=%zu cap=%zu\n",
		stack->len, stack->cap);
	i = 0;
	while (i < stack->len)
	{
		item = items[i];
		branch = " ├──";
		if (i + 1 == stack->len)
			branch = " ╰──";
		fprintf(stderr, "%s[%3zu] item=%p", branch, i, (void *)item);
		if (item == NULL)
			fprintf(stderr, " (null)\n");
		else
			fprintf(stderr, " %s start=%zu end=%zu len=%zu\n",
				debug_context_to_string(item->context),
				item->start,
				item->end,
				item->end - item->start);
		i++;
	}
}

/* ************************************************************************* */
/*                                    CST                                    */
/* ************************************************************************* */

#ifdef DEBUG_CST
static inline void	cst_log_prefix(bool *lasts, size_t depth)
{
	size_t	i;

	i = 1;
	while (i < depth)
	{
		if (lasts[i])
			fprintf(stderr, "    ");
		else
			fprintf(stderr, " │  ");
		i++;
	}
}

static inline void	cst_log_branch(bool *lasts, size_t depth, bool is_last)
{
	if (depth == 0)
		return ;
	cst_log_prefix(lasts, depth);
	if (is_last)
		fprintf(stderr, " ╰──");
	else
		fprintf(stderr, " ├──");
}

static inline void	cst_log_span(t_cst_node *node)
{
	size_t	token_end_id;

	if (node->tokens_count == 0)
	{
		fprintf(stderr, " tokens=empty");
		return ;
	}
	token_end_id = node->tokens_start_id + node->tokens_count - 1;
	fprintf(stderr, " tokens=%zu-%zu (%zu)",
		node->tokens_start_id, token_end_id, node->tokens_count);
}

static inline void	cst_log_heredoc_body(t_cst_node *node)
{
	if (node->heredoc_body.data == NULL && node->heredoc_body.len == 0)
		return ;
	fprintf(stderr, " heredoc_body={len=%zu cap=%zu data=",
		node->heredoc_body.len, node->heredoc_body.cap);
	dump_string_value(&node->heredoc_body);
	fprintf(stderr, "}");
}

static void	cst_log_node(t_cst_node *node, size_t depth, bool *lasts, bool is_last)
{
	size_t		i;
	const char	*color;

	if (!node)
		return ;
	color = NC;
	if (node->symbol <= SYM_TERMINAL_MAX)
		color = RED;
	else if (node->symbol <= SYM_complete_command)
		color = GREEN;
	else if (node->symbol <= SYM_NON_TERMINAL_MAX)
		color = YELLOW;
	cst_log_branch(lasts, depth, is_last);
	fprintf(stderr, "%s%s%s", color, symbol_to_string(node->symbol), NC);
	if (node->rule_id != RULE_NONE)
		fprintf(stderr, " rule=%i", (int)node->rule_id);
	cst_log_span(node);
	cst_log_heredoc_body(node);
	fprintf(stderr, "\n");
	lasts[depth] = is_last;
	i = 0;
	while (i < node->child_count)
	{
		cst_log_node(node->children[i], depth + 1, lasts,
			i + 1 == node->child_count);
		i++;
	}
}
#endif

void	dump_cst(t_cst_node *node)
{
#ifdef DEBUG_CST
	bool	lasts[256];

	if (!node)
		return ;
	fprintf(stderr, "[BUILDR] CST built:\n");
	cst_log_node(node, 0, lasts, true);
#else
	(void)node;
#endif
}

/* ************************************************************************* */
/*                                    AST                                    */
/* ************************************************************************* */

const char	*ast_command_type_to_string(t_ast_command_type type)
{
	if (type == AST_CMD_SIMPLE)
		return ("SIMPLE");
	if (type == AST_CMD_LIST)
		return ("LIST");
	if (type == AST_CMD_IF)
		return ("IF");
	if (type == AST_CMD_FOR)
		return ("FOR");
	if (type == AST_CMD_LOOP)
		return ("LOOP");
	if (type == AST_CMD_CASE)
		return ("CASE");
	if (type == AST_CMD_FUNCTION_DEF)
		return ("FUNCTION_DEF");
	return ("INVALID");
}

#ifdef DEBUG_AST
#define AST_AT(type, vec, i) (&((type *)(vec)->data)[i])

static inline const char	*ast_bool(bool value)
{
	if (value)
		return ("true");
	return ("false");
}

static inline void	ast_log_prefix(bool *lasts, size_t depth)
{
	size_t	i;

	i = 1;
	while (i < depth)
	{
		if (lasts[i])
			fprintf(stderr, "    ");
		else
			fprintf(stderr, " │  ");
		i++;
	}
}

static inline void	ast_log_branch(bool *lasts, size_t depth, bool is_last)
{
	if (depth == 0)
		return ;
	ast_log_prefix(lasts, depth);
	if (is_last)
		fprintf(stderr, " ╰──");
	else
		fprintf(stderr, " ├──");
}

static inline void	ast_log_head(
	bool *lasts,
	size_t depth,
	bool is_last,
	const char *color,
	const char *name)
{
	ast_log_branch(lasts, depth, is_last);
	fprintf(stderr, "%s%s%s", color, name, NC);
	lasts[depth] = is_last;
}

static void	ast_log_token_value(t_token *token)
{
	size_t	i;
	char	c;

	fprintf(stderr, " (%s", BLUE);
	i = 0;
	while (i < token->value.len)
	{
		c = ((char *)token->value.data)[i];
		if (c == '\n')
			fprintf(stderr, "\\n");
		else if (c == '\t')
			fprintf(stderr, "\\t");
		else if (c == '\r')
			fprintf(stderr, "\\r");
		else if (c == '\\')
			fprintf(stderr, "\\");
		else
			fprintf(stderr, "%c", c);
		i++;
	}
	fprintf(stderr, "%s)", NC);
}

static void	ast_log_token(const char *name, t_token *token)
{
	fprintf(stderr, " %s", name);
	ast_log_token_value(token);
}

static void	ast_log_string(const char *name, t_string *value)
{
	fprintf(stderr, " %s={len=%zu cap=%zu data=",
		name, value->len, value->cap);
	dump_string_value(value);
	fprintf(stderr, "}");
}

static const char	*ast_redir_op_to_string(t_ast_redir_op op)
{
	if (op == AST_REDIR_READ)
		return ("READ");
	if (op == AST_REDIR_HEREDOC)
		return ("HEREDOC");
	if (op == AST_REDIR_DUP_READ)
		return ("DUP_READ");
	if (op == AST_REDIR_WRITE)
		return ("WRITE");
	if (op == AST_REDIR_APPEND)
		return ("APPEND");
	if (op == AST_REDIR_DUP_WRITE)
		return ("DUP_WRITE");
	if (op == AST_REDIR_CLOBBER)
		return ("CLOBBER");
	if (op == AST_REDIR_READ_WRITE)
		return ("READ_WRITE");
	return ("INVALID");
}

static void	ast_log_list(
	const char *name,
	t_ast_list *list,
	size_t depth,
	bool *lasts,
	bool is_last);

static void	ast_log_token_ast_vector(
	const char *name,
	t_token *token,
	size_t depth,
	bool *lasts,
	bool is_last);

static void	ast_log_redirection(
	t_ast_redirection *redir,
	size_t depth,
	bool *lasts,
	bool is_last)
{
	size_t	child_count;
	size_t	child_id;

	child_count = 0;
	if (redir->is_location && redir->location.ast_vector.len > 0)
		child_count++;
	if (redir->operation != AST_REDIR_HEREDOC
		&& redir->word.ast_vector.len > 0)
		child_count++;
	child_id = 0;
	ast_log_head(lasts, depth, is_last, RED, "REDIRECTION");
	fprintf(stderr, " op=%s", ast_redir_op_to_string(redir->operation));
	fprintf(stderr, " fd=%d", redir->fd);
	fprintf(stderr, " is_location=%s", ast_bool(redir->is_location));
	if (redir->is_location)
		ast_log_token("location", &redir->location);
	if (redir->operation == AST_REDIR_HEREDOC)
		ast_log_string("heredoc_body", &redir->heredoc_body);
	else
		ast_log_token("word", &redir->word);
	fprintf(stderr, " expand_heredoc_body=%s",
		ast_bool(redir->expand_heredoc_body));
	fprintf(stderr, "\n");
	if (redir->is_location && redir->location.ast_vector.len > 0)
		ast_log_token_ast_vector("LOCATION_AST_VECTOR", &redir->location,
			depth + 1, lasts, ++child_id == child_count);
	if (redir->operation != AST_REDIR_HEREDOC
		&& redir->word.ast_vector.len > 0)
		ast_log_token_ast_vector("WORD_AST_VECTOR", &redir->word,
			depth + 1, lasts, ++child_id == child_count);
}

static void	ast_log_redir_list(
	const char *name,
	t_ast_redir_list *redirs,
	size_t depth,
	bool *lasts,
	bool is_last)
{
	size_t	i;

	ast_log_head(lasts, depth, is_last, RED, name);
	fprintf(stderr, " count=%zu\n", redirs->len);
	i = 0;
	while (i < redirs->len)
	{
		ast_log_redirection(AST_AT(t_ast_redirection, redirs, i),
			depth + 1, lasts, i + 1 == redirs->len);
		i++;
	}
}

static void	ast_log_token_ast_vector(
	const char *name,
	t_token *token,
	size_t depth,
	bool *lasts,
	bool is_last)
{
	size_t		i;
	t_ast_root	*root;

	if (token->ast_vector.len == 0)
		return ;
	ast_log_head(lasts, depth, is_last, GREEN, name);
	fprintf(stderr, " count=%zu\n", token->ast_vector.len);
	i = 0;
	while (i < token->ast_vector.len)
	{
		root = AST_AT(t_ast_root, &token->ast_vector, i);
		ast_log_list("AST_ROOT", root, depth + 1, lasts,
			i + 1 == token->ast_vector.len);
		i++;
	}
}

static void	ast_log_token_ast_roots(
	t_token *token,
	size_t depth,
	bool *lasts)
{
	size_t		i;
	t_ast_root	*root;

	i = 0;
	while (i < token->ast_vector.len)
	{
		root = AST_AT(t_ast_root, &token->ast_vector, i);
		ast_log_list("AST_ROOT", root, depth, lasts,
			i + 1 == token->ast_vector.len);
		i++;
	}
}

static void	ast_log_token_vector(
	const char *name,
	const char *item_name,
	t_token_pool *vector,
	size_t depth,
	bool *lasts,
	bool is_last)
{
	size_t	i;
	t_token	*token;

	ast_log_head(lasts, depth, is_last, CYAN, name);
	fprintf(stderr, " count=%zu\n", vector->len);
	i = 0;
	while (i < vector->len)
	{
		token = AST_AT(t_token, vector, i);
		ast_log_head(lasts, depth + 1, i + 1 == vector->len,
			CYAN, item_name);
		ast_log_token_value(token);
		fprintf(stderr, "\n");
		ast_log_token_ast_roots(token, depth + 2, lasts);
		i++;
	}
}

static void	ast_log_token_pattern(
	const char *name,
	t_token_pool *pattern,
	size_t depth,
	bool *lasts,
	bool is_last)
{
	ast_log_head(lasts, depth, is_last, CYAN, name);
	fprintf(stderr, " count=%zu\n", pattern->len);
	ast_log_token_vector("TOKENS", "TOKEN", pattern, depth + 1, lasts, true);
}

static void	ast_log_command(
	t_ast_command *command,
	size_t depth,
	bool *lasts,
	bool is_last);

static void	ast_log_simple_command(
	t_ast_scmd *cmd,
	size_t depth,
	bool *lasts,
	bool is_last)
{
	size_t	child_count;
	size_t	child_id;

	child_count = 3;
	child_id = 0;
	ast_log_head(lasts, depth, is_last, GREEN, "SIMPLE_COMMAND");
	fprintf(stderr, " assignments=%zu words=%zu redirs=%zu\n",
		cmd->assignments.len, cmd->words.len, cmd->redirs.len);
	ast_log_token_vector("ASSIGNMENTS", "ASSIGNMENT",
		&cmd->assignments, depth + 1, lasts, ++child_id == child_count);
	ast_log_token_vector("WORDS", "WORD",
		&cmd->words, depth + 1, lasts, ++child_id == child_count);
	ast_log_redir_list("REDIRS", &cmd->redirs,
		depth + 1, lasts, ++child_id == child_count);
}

static void	ast_log_pipeline(
	t_ast_pipeline *pipeline,
	size_t depth,
	bool *lasts,
	bool is_last,
	const char *next_op)
{
	size_t	i;

	ast_log_head(lasts, depth, is_last, YELLOW, "PIPELINE");
	fprintf(stderr, " negated=%s commands=%zu", ast_bool(pipeline->negated),
		pipeline->commands.len);
	if (next_op)
		fprintf(stderr, " next=%s", next_op);
	fprintf(stderr, "\n");
	i = 0;
	while (i < pipeline->commands.len)
	{
		ast_log_command(AST_AT(t_ast_command, &pipeline->commands, i),
			depth + 1, lasts, i + 1 == pipeline->commands.len);
		i++;
	}
}

static void	ast_log_and_or(
	t_ast_and_or *and_or,
	size_t depth,
	bool *lasts,
	bool is_last,
	bool async)
{
	size_t		i;
	bool		*ops;
	const char	*next_op;

	ast_log_head(lasts, depth, is_last, YELLOW, "AND_OR");
	fprintf(stderr, " pipelines=%zu operators=%zu async=%s\n",
		and_or->pipelines.len, and_or->next_on_success.len,
		ast_bool(async));
	ops = (bool *)and_or->next_on_success.data;
	i = 0;
	while (i < and_or->pipelines.len)
	{
		next_op = NULL;
		if (i < and_or->next_on_success.len)
		{
			if (ops[i])
				next_op = "&&";
			else
				next_op = "||";
		}
		ast_log_pipeline(AST_AT(t_ast_pipeline, &and_or->pipelines, i),
			depth + 1, lasts, i + 1 == and_or->pipelines.len, next_op);
		i++;
	}
}

static void	ast_log_list(
	const char *name,
	t_ast_list *list,
	size_t depth,
	bool *lasts,
	bool is_last)
{
	size_t	i;
	bool	*asyncs;

	ast_log_head(lasts, depth, is_last, GREEN, name);
	fprintf(stderr, " and_ors=%zu asyncs=%zu subshell=%s\n",
		list->and_ors.len, list->asyncs.len, ast_bool(list->subshell));
	asyncs = (bool *)list->asyncs.data;
	i = 0;
	while (i < list->and_ors.len)
	{
		ast_log_and_or(AST_AT(t_ast_and_or, &list->and_ors, i),
			depth + 1, lasts, i + 1 == list->and_ors.len, asyncs[i]);
		i++;
	}
}

static void	ast_log_if(
	t_ast_if *if_node,
	size_t depth,
	bool *lasts,
	bool is_last)
{
	size_t	i;
	size_t	total;
	size_t	id;

	total = if_node->conditions.len * 2 + if_node->has_else;
	id = 0;
	ast_log_head(lasts, depth, is_last, MAGENTA, "IF");
	fprintf(stderr, " branches=%zu has_else=%s\n",
		if_node->conditions.len, ast_bool(if_node->has_else));
	i = 0;
	while (i < if_node->conditions.len)
	{
		ast_log_list("CONDITION", AST_AT(t_ast_list, &if_node->conditions, i),
			depth + 1, lasts, ++id == total);
		ast_log_list("BODY", AST_AT(t_ast_list, &if_node->bodies, i),
			depth + 1, lasts, ++id == total);
		i++;
	}
	if (if_node->has_else)
		ast_log_list("ELSE", &if_node->else_body,
			depth + 1, lasts, true);
}

static void	ast_log_for(
	t_ast_for *for_node,
	size_t depth,
	bool *lasts,
	bool is_last)
{
	size_t	child_count;
	size_t	child_id;

	child_count = 2;
	if (for_node->var_name.ast_vector.len > 0)
		child_count++;
	child_id = 0;
	ast_log_head(lasts, depth, is_last, MAGENTA, "FOR");
	ast_log_token("var", &for_node->var_name);
	fprintf(stderr, " words=%zu\n", for_node->words.len);
	if (for_node->var_name.ast_vector.len > 0)
		ast_log_token_ast_vector("VAR_AST_VECTOR", &for_node->var_name,
			depth + 1, lasts, ++child_id == child_count);
	ast_log_token_vector("WORDS", "WORD", &for_node->words,
		depth + 1, lasts, ++child_id == child_count);
	ast_log_list("BODY", &for_node->body, depth + 1, lasts,
		++child_id == child_count);
}

static void	ast_log_loop(
	t_ast_loop *loop,
	size_t depth,
	bool *lasts,
	bool is_last)
{
	ast_log_head(lasts, depth, is_last, MAGENTA, "LOOP");
	fprintf(stderr, " condition_must_be_true=%s\n",
		ast_bool(loop->condition_must_be_true));
	ast_log_list("CONDITION", &loop->condition, depth + 1, lasts, false);
	ast_log_list("BODY", &loop->body, depth + 1, lasts, true);
}

static void	ast_log_case_item(
	t_ast_case *case_node,
	size_t index,
	size_t depth,
	bool *lasts,
	bool is_last)
{
	bool	*fallthrough;

	fallthrough = (bool *)case_node->fallthrough.data;
	ast_log_head(lasts, depth, is_last, MAGENTA, "CASE_ITEM");
	fprintf(stderr, " index=%zu fallthrough=%s\n",
		index, ast_bool(fallthrough[index]));
	ast_log_token_pattern("PATTERN",
		AST_AT(t_token_pool, &case_node->patterns, index),
		depth + 1, lasts, false);
	ast_log_list("BODY", AST_AT(t_ast_list, &case_node->bodies, index),
		depth + 1, lasts, true);
}

static void	ast_log_case(
	t_ast_case *case_node,
	size_t depth,
	bool *lasts,
	bool is_last)
{
	size_t	i;
	size_t	child_count;
	size_t	child_id;

	child_count = case_node->patterns.len;
	if (case_node->word.ast_vector.len > 0)
		child_count++;
	child_id = 0;
	ast_log_head(lasts, depth, is_last, MAGENTA, "CASE");
	ast_log_token("word", &case_node->word);
	fprintf(stderr, " items=%zu\n", case_node->patterns.len);
	if (case_node->word.ast_vector.len > 0)
		ast_log_token_ast_vector("WORD_AST_VECTOR", &case_node->word,
			depth + 1, lasts, ++child_id == child_count);
	i = 0;
	while (i < case_node->patterns.len)
	{
		ast_log_case_item(case_node, i, depth + 1, lasts,
			++child_id == child_count);
		i++;
	}
}

static void	ast_log_function(
	t_ast_function_def *function,
	size_t depth,
	bool *lasts,
	bool is_last)
{
	size_t	child_count;
	size_t	id;

	child_count = 0;
	if (function->body)
		child_count++;
	if (function->redirs.len > 0)
		child_count++;
	if (function->name.ast_vector.len > 0)
		child_count++;
	id = 0;
	ast_log_head(lasts, depth, is_last, MAGENTA, "FUNCTION_DEF");
	ast_log_token("name", &function->name);
	fprintf(stderr, " redirs=%zu\n", function->redirs.len);
	if (function->name.ast_vector.len > 0)
		ast_log_token_ast_vector("NAME_AST_VECTOR", &function->name,
			depth + 1, lasts, ++id == child_count);
	if (function->body)
		ast_log_command(function->body, depth + 1, lasts,
			++id == child_count);
	if (function->redirs.len > 0)
		ast_log_redir_list("REDIRS", &function->redirs,
			depth + 1, lasts, ++id == child_count);
}

static void	ast_log_command_data(
	t_ast_command *command,
	size_t depth,
	bool *lasts,
	bool is_last)
{
	if (command->type == AST_CMD_SIMPLE)
		ast_log_simple_command(&command->data.simple, depth, lasts, is_last);
	else if (command->type == AST_CMD_LIST)
		ast_log_list("LIST", &command->data.list, depth, lasts, is_last);
	else if (command->type == AST_CMD_IF)
		ast_log_if(&command->data.if_clause, depth, lasts, is_last);
	else if (command->type == AST_CMD_FOR)
		ast_log_for(&command->data.for_clause, depth, lasts, is_last);
	else if (command->type == AST_CMD_LOOP)
		ast_log_loop(&command->data.loop, depth, lasts, is_last);
	else if (command->type == AST_CMD_CASE)
		ast_log_case(&command->data.case_clause, depth, lasts, is_last);
	else if (command->type == AST_CMD_FUNCTION_DEF)
		ast_log_function(&command->data.function_def, depth, lasts, is_last);
}

static void	ast_log_command(
	t_ast_command *command,
	size_t depth,
	bool *lasts,
	bool is_last)
{
	ast_log_head(lasts, depth, is_last, BLUE, "COMMAND");
	fprintf(stderr, " type=%s redirs=%zu\n",
		ast_command_type_to_string(command->type), command->redirs.len);
	ast_log_command_data(command, depth + 1, lasts,
		command->redirs.len == 0);
	if (command->redirs.len > 0)
		ast_log_redir_list("COMMAND_REDIRS", &command->redirs,
			depth + 1, lasts, true);
}
#endif

void	dump_ast(t_ast_root *root)
{
#ifdef DEBUG_AST
	bool	lasts[256];

	if (!root)
		return ;
	ast_log_list("AST_ROOT", root, 0, lasts, true);
#else
	(void)root;
#endif
}
