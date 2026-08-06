#include "debug.h"
#include "shell.h"
#include "grammar_actions.h"
#include "grammar_gotos.h"
#include "grammar_symbols.h"
#include "token.h"
#include "lr_tables.h"
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
#include "variables_priv.h"
#include <stdlib.h>
#include <assert.h>	// DEBUG


/* ************************************************************************* */
/*                                     ENV                                   */
/* ************************************************************************* */

static inline void	positionals_dump_depth(t_positionals_stack *stack, size_t depth)
{
	t_positionals	*positionals;
	size_t			count;
	size_t			i;
	t_string		*param;

	positionals = &((t_positionals *)stack->data)[depth];
	count = positionals->len;
	i = 0;
	while (i < count)
	{
		param = &((t_string *)positionals->data)[i];
		fprintf(stderr, "POSITIONALS[%zu] %zu='%s'\n", depth, i, param->data);
		i++;
	}
	fprintf(stderr, "POSITIONALS #=%zu\n", count);
}

void	positionals_dump(void)
{
	t_shell 			*shell;
	t_positionals_stack	*stack;
	size_t				count;
	size_t				i;

	fprintf(stderr, "\nDUMP POSITIONALS\n");
	shell = shell_get();
	if (!shell)
		error_print(error(ERR_SHELL_NOT_FOUND), "positionals_dump()", NULL, NULL);
	stack = &shell->params.positionals_stack;
	count = stack->len;
	i = 0;
	while (i < count)
	{
		positionals_dump_depth(stack, i);
		i++;
		if (i < count)
			fprintf(stderr, "---\n");
	}
}

const char	*option_to_string(t_option option)
{
	if (option == OPT_EXPORT_ALL)
		return ("a");
	else if (option == OPT_NOTIFY)
		return ("b");
	else if (option == OPT_NOCLOBBER)
		return ("C");
	else if (option == OPT_ERREXIT)
		return ("e");
	else if (option == OPT_NOGLOB)
		return ("f");
	else if (option == OPT_CMD_HASH)
		return ("h");
	else if (option == OPT_INTERACTIVE)
		return ("i");
	else if (option == OPT_MONITOR)
		return ("m");
	else if (option == OPT_NOEXEC)
		return ("n");
	else if (option == OPT_NOUNSET)
		return ("u");
	else if (option == OPT_VERBOSE)
		return ("v");
	else if (option == OPT_XTRACE)
		return ("x");
	else if (option == OPT_CMD_STRING)
		return ("c");
	else if (option == OPT_STDIN_INPUT)
		return ("s");
	else if (option == OPT_IGNOREEOF)
		return ("ignoreeof");
	else if (option == OPT_NOLOG)
		return ("nolog");
	else if (option == OPT_PIPEFAIL)
		return ("pipefail");
	else if (option == OPT_VI)
		return ("vi");
	return ("unknown");
}

void	options_dump(void)
{
	bool			is_active;
	unsigned int	option;
	const char		*name;
	const char		*value;
	t_error			err;

	fprintf(stderr, "\nDUMP OPTIONS\n");
	option = 1u << 0;
	while (option <= OPT_VI)
	{
		name = option_to_string(option);
		err = option_is_active(option, &is_active);
		if (err.type)
			(void)error_print(err, __func__, "option_is_active() failed", NULL, NULL);
		else
		{
			value = bool_to_string(is_active);
			fprintf(stderr, "OPTION %s=%s\n", name, value);
		}
		option <<= 1;
	}
}

void	specials_dump(void)
{
	t_shell 	*shell;
	t_specials	*specials;

	fprintf(stderr, "\nDUMP SPECIALS\n");
	shell = shell_get();
	if (!shell)
		error_print(error(ERR_SHELL_NOT_FOUND), "specials_dump()", NULL, NULL);
	specials = &shell->params.specials;
	if (specials->source.len > 0)
		fprintf(stderr, "SPECIAL source='%s'\n", specials->source.data);
	else
		fprintf(stderr, "SPECIAL source=NULL\n");
	if (specials->zero.len > 0)
		fprintf(stderr, "SPECIAL 0='%s'\n", specials->zero.data);
	else
		fprintf(stderr, "SPECIAL 0=NULL\n");
	fprintf(stderr, "SPECIAL $=%jd\n", (intmax_t)specials->pid);
	fprintf(stderr, "SPECIAL !=%jd\n", (intmax_t)specials->last_bg_pid);
	fprintf(stderr, "SPECIAL ?=%i\n", specials->last_status);
}

/* ************************************************************************* */
/*                                 FT_GETOPT                                 */
/* ************************************************************************* */

static void	ft_getopt_dump_flag_with_arg(t_getopt_flag_with_arg *flag)
{
	size_t	i;

	fprintf(stderr, "[%c%c", flag->sign, flag->flag);
	if (flag->arguments_are_optional)
		fprintf(stderr, "[");
	else
		fprintf(stderr, " ");
	i = 0;
	while (flag->arguments_valids[i])
	{
		fprintf(stderr, "%s", flag->arguments_valids[i]);
		if (flag->arguments_valids[i + 1])
			fprintf(stderr, " ");
		i++;
	}
	if (flag->arguments_are_optional)
		fprintf(stderr, "]");
	fprintf(stderr, "]\n");
}

void	dump_getopt_in(t_getopt_in *in)
{
	size_t	i;

	fprintf(stderr, "\nGETOPT DUMP IN\n");
	fprintf(stderr, "builtin_name=%s\n", in->builtin_name);
	fprintf(stderr, "valid_minus_flags=%s\n", in->valid_minus_flags);
	fprintf(stderr, "valid_plus_flags=%s\n", in->valid_plus_flags);
	i = 0;
	while (i < in->options_with_arg_count)
	{
		ft_getopt_dump_flag_with_arg(&in->options_with_arg[i]);
		i++;
	}
	fprintf(stderr, "options_with_arg_count=%zu\n", in->options_with_arg_count);
	fprintf(stderr, "single_delimiter=%s\n", bool_to_string(in->single_delimiter));
	fprintf(stderr, "ub_on_repeated_flags=%s\n", bool_to_string(in->ub_on_repeated_flags));
}

void	dump_getopt_out(t_getopt_out *out)
{
	size_t			i;
	t_getopt_option	*option;

	fprintf(stderr, "\nGETOPT DUMP OUT\n");
	i = 0;
	while (i < out->options.len)
	{
		option = &((t_getopt_option *)out->options.data)[i];
		if (option->argument)
			fprintf(stderr, "%c%c %s\n", option->sign, option->flag, option->argument);
		else
			fprintf(stderr, "%c%c\n", option->sign, option->flag);
		i++;
	}
	fprintf(stderr, "first_operand_index=%zu\n", out->first_operand_index);
}

void	dump_getopt_all(t_getopt_in *in, t_getopt_out *out)
{
	dump_getopt_in(in);
	dump_getopt_out(out);
}

/* ************************************************************************* */
/*                                    ENV                                    */
/* ************************************************************************* */

static void	dump_env_scalar_cst(const char *name_cst)
{
	t_string	value;
	t_error		err;

	assert(name_cst != NULL);
	assert(name_cst[0] != '\0');
	err = env_get_from_const(name_cst, &value);
	if (err.type != ERR_NO)
	{
		fprintf(stderr, "PARAMS '%s'=[ERROR: '%s']\n", name_cst, error_to_string(err));
		return ;
	}
	if (value.data)
	{
		fprintf(stderr, "PARAMS '%s'='%s'\n", name_cst, value.data);
		string_free(&value);
	}
	else
		fprintf(stderr, "PARAMS '%s'=NULL\n", name_cst);
}

static void	dump_env_variables(void)
{
	t_shell				*shell;
	const t_key_value	**var_list;
	size_t				i;

	shell = shell_get();
	if (!shell)
	{
		error_print(error(ERR_SHELL_NOT_FOUND), "dump_env_variables()", NULL, NULL);
		return ;
	}
	var_list = hashmap_get_all(&shell->params.variables);
	if (var_list == NULL)
	{
		error_print(error_sys(), "dump_env_variables()", NULL, NULL);
		return ;
	}
	i = 0;
	while (var_list[i] != NULL)
	{
		dump_env_scalar_cst(var_list[i]->key);
		i++;
	}
	free(var_list);
}

static void	dump_env_options(void)
{
	dump_env_scalar_cst("-");
}

static void	dump_env_specials(void)
{
	dump_env_scalar_cst("0");
	dump_env_scalar_cst("$");
	dump_env_scalar_cst("!");
	dump_env_scalar_cst("?");
}

static void	dump_env_positionals(void)
{
	t_shell		*shell;
	t_error		err;
	t_string	name_string;
	t_string	count_s;
	size_t		count;
	size_t		i;
	char		*name;

	shell = shell_get();
	if (!shell)
	{
		error_print(error(ERR_SHELL_NOT_FOUND), "dump_env_positionals()", NULL, NULL);
		return ;
	}
	string_init(&name_string, 0, "#", -1);
	err = positionals_get_one(&shell->params.positionals_stack, &name_string, &count_s);
	string_free(&name_string);
	if (err.type != ERR_NO)
	{
		error_print(err, "dump_env_positionals()", NULL, NULL);
		return ;
	}
	count = ft_atozu(count_s.data);
	string_free(&count_s);
	i = 1;
	while (i <= count)
	{
		name = ft_zutoa(i);
		if (!name)
		{
			error_print(error_sys(), "dump_env_positionals()", NULL, NULL);
			break ;
		}
		dump_env_scalar_cst(name);
		free(name);
		i++;
	}
	dump_env_scalar_cst("#");
}

void	dump_env(void)
{
	fprintf(stderr, "\nDUMP PARAMS\n");
	dump_env_variables();
	dump_env_options();
	dump_env_specials();
	dump_env_positionals();
}

/* ************************************************************************* */
/*                                 VARIABLES                                 */
/* ************************************************************************* */

static inline void	dump_var_one_priv(const char *name, const t_var *var)
{
	const char	*value;

	if (var->value.data)
		value = var->value.data;
	else
		value = "(NULL)";
	fprintf(stderr, "VAR name='%s' value='%s' exported=%s readonly=%s\n",
		name,
		value,
		bool_to_string(var->export),
		bool_to_string(var->readonly));
}

void	dump_var_one(const char *name)
{
	t_params 	*params;
	const t_var	*value;

	assert(name != NULL);
	params = shell_get_params();
	assert(params != NULL);
	value = hashmap_get_const(&params->variables, name);
	if (value == NULL)
		fprintf(stderr, "VAR '%s' is not set.\n", name);
	else
		dump_var_one_priv(name, value);
}

void	dump_variables(void)
{
	t_params 			*params;
	const t_key_value	**list;
	size_t				i;

	fprintf(stderr, "\nDUMP VARIABLES\n");
	params = shell_get_params();
	assert(params != NULL);
	list = hashmap_get_all(&params->variables);
	if (list == NULL)
	{
		(void)error_print(error_sys(), __func__, NULL, NULL);
		return ;
	}
	i = 0;
	while (list[i] != NULL)
	{
		dump_var_one_priv(list[i]->key, list[i]->value);
		i++;
	}
	free(list);
}

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
	int		ret;

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
		default:
			ret = asprintf(&formatted, "unknown (%i)", (int)token_type);
			(void)ret;
			return (formatted);
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

void	dump_rule(const t_lr_tables *tables, size_t rule_id)
{
	const t_lr_rule	*rule;

	if (tables == NULL)
		return ((void)fprintf(stderr, "[RULE] (null tables)\n"));
	rule = &tables->rules[rule_id];
	fprintf(stderr, "[RULE] %zu lhs=%s rhs_len=%zu\n",
		rule_id,
		symbol_to_string(rule->lhs),
		rule->rhs_len);
}

/* ************************************************************************* */
/*                                 LR_STATE                                  */
/* ************************************************************************* */

static void	dump_lr_state_action(
				const t_lr_tables *tables,
				size_t lr_state_id,
				t_symbol symbol)
{
	const t_action	*action;

	if ((size_t)symbol >= ACTION_COL_COUNT)
		return ;
	action = &tables->actions[lr_state_id * ACTION_COL_COUNT + symbol];
	fprintf(stderr, "action[%s]=%s:%zu\n",
		symbol_to_string(symbol),
		action_type_to_string(action->type),
		action->payload);
}

static void	dump_lr_state_gotos(const t_lr_tables *tables, size_t lr_state_id)
{
	size_t		i;
	size_t		lr_state_to;
	t_symbol	symbol;

	i = 0;
	while (i < GOTO_COL_COUNT)
	{
		symbol = (t_symbol)(SYM_NON_TERMINAL_MIN + i);
		lr_state_to = tables->gotos[lr_state_id * GOTO_COL_COUNT + i];
		if (lr_state_to != GOTO_EMPTY)
			fprintf(stderr, "goto[%s]=%zu\n",
				symbol_to_string(symbol),
				lr_state_to);
		i++;
	}
}

void	dump_lr_state(const t_lr_tables *tables, size_t lr_state_id)
{
	if (tables == NULL)
		return ((void)fprintf(stderr, "[STATE] (null tables)\n"));
	fprintf(stderr, "\n[STATE %zu]\n", lr_state_id);
	fprintf(stderr, "qualifier=%p expects_cmd_name_or_word=%s\n",
		tables->qualifiers[lr_state_id],
		bool_to_string(tables->expects_cmd_name_or_word[lr_state_id]));
	dump_lr_state_action(tables, lr_state_id, SYM_Lbrace);
	dump_lr_state_action(tables, lr_state_id, SYM_WORD);
	dump_lr_state_action(tables, lr_state_id, SYM_NEWLINE);
	dump_lr_state_gotos(tables, lr_state_id);
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

/* ************************************************************************* */
/*                                HISTORY                                    */
/* ************************************************************************* */

void	history_load_start_logs(const char *func_name)
{
	print_title("%s()", func_name);
}

void	history_load_end_logs(const char *func_name)
{
	print_result("%s()", func_name);
}

void	success_history_adapter_add_log(t_history_adapter *history_adapter)
{
	print_pass("entries uploaded to readline           %i\n", (int)history_adapter->count);
}

void	history_file_save_start_log(t_history_file *history_file)
{
	if (history_file->path.len == 0)
		print_warn("[HISTORY] History disabled: %sskipping save%s\n", YELLOW, NC);
	else if (history_file->content.len == 0)
		print_warn("[HISTORY] History empty: %sskipping save%s\n", YELLOW, NC);
}

void	history_file_save_end_log(t_history_file *history_file)
{
	if (history_file->err.type == ERR_NO)
		print_pass("[HISTORY] History saved to = %s%s%s\n", BLUE, history_file->path.data, NC);
}

void	empty_history_file_load_log(void)
{
	print_warn("entries loaded from history file       %s0%s\n", YELLOW, NC);
}

void	success_history_file_load_log(t_history_file *history_file)
{
	print_pass("entries loaded from history file       %i\n", (int)history_file->loaded_count);
}

void	history_load_file_path_from_logs(const char *path, const char *origin)
{
	print_pass("history file path from $%s           '%s%s%s'\n", origin, BLUE, path, GREY);
}

void	history_load_max_size_from_unset_logs(void)
{
	print_pass("history max size                       default (INFINITE)\n");
}

void	history_load_max_size_from_invalid_logs(void)
{
	print_pass("history max size                       $HISTSIZE invalid, default (INFINITE)\n");
}

void	history_load_max_size_from_logs(ssize_t max)
{
	print_pass("history max size from $HISTSIZE        %li\n", max);
}
