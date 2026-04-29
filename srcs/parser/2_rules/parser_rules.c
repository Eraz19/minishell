#include "parser_rules__priv.h"
#include "libft.h"

static void	init_remaining_rules(t_rule *rules);

void	parser_rules_init(t_rule *rules)
{
	ft_bzero(rules, RULE_COUNT * sizeof(*rules));
	parser_rules_init_and_or(rules);
	parser_rules_init_brace_group(rules);
	parser_rules_init_case_clause(rules);
	parser_rules_init_case_item_ns(rules);
	parser_rules_init_case_item(rules);
	parser_rules_init_case_list_ns(rules);
	parser_rules_init_case_list(rules);
	parser_rules_init_cmd_name(rules);
	parser_rules_init_cmd_prefix(rules);
	parser_rules_init_cmd_suffix(rules);
	parser_rules_init_cmd_word(rules);
	parser_rules_init_command(rules);
	parser_rules_init_complete_command(rules);
	parser_rules_init_complete_commands(rules);
	parser_rules_init_compound_command(rules);
	parser_rules_init_compound_list(rules);
	parser_rules_init_do_group(rules);
	parser_rules_init_else_part(rules);
	parser_rules_init_filename(rules);
	parser_rules_init_fname(rules);
	parser_rules_init_for_clause(rules);
	parser_rules_init_function_body(rules);
	init_remaining_rules(rules);
}

static void	init_remaining_rules(t_rule *rules)
{
	parser_rules_init_function_definition(rules);
	parser_rules_init_here_end(rules);
	parser_rules_init_if_clause(rules);
	parser_rules_init_in(rules);
	parser_rules_init_io_file(rules);
	parser_rules_init_io_here(rules);
	parser_rules_init_io_redirect(rules);
	parser_rules_init_linebreak(rules);
	parser_rules_init_list(rules);
	parser_rules_init_name(rules);
	parser_rules_init_newline_list(rules);
	parser_rules_init_pattern_list(rules);
	parser_rules_init_pipe_sequence(rules);
	parser_rules_init_pipeline(rules);
	parser_rules_init_program(rules);
	parser_rules_init_redirect_list(rules);
	parser_rules_init_separator_op(rules);
	parser_rules_init_separator(rules);
	parser_rules_init_sequential_sep(rules);
	parser_rules_init_simple_command(rules);
	parser_rules_init_subshell(rules);
	parser_rules_init_term(rules);
	parser_rules_init_until_clause(rules);
	parser_rules_init_while_clause(rules);
	parser_rules_init_wordlist(rules);
}
