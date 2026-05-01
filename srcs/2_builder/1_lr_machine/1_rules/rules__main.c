#include "rules__priv.h"
#include "libft.h"

static void	init_remaining_rules(t_rule *rules);

void	rules_init(t_rule *rules)
{
	ft_bzero(rules, RULE_COUNT * sizeof(*rules));
	rules_init_and_or(rules);
	rules_init_brace_group(rules);
	rules_init_case_clause(rules);
	rules_init_case_item_ns(rules);
	rules_init_case_item(rules);
	rules_init_case_list_ns(rules);
	rules_init_case_list(rules);
	rules_init_cmd_name(rules);
	rules_init_cmd_prefix(rules);
	rules_init_cmd_suffix(rules);
	rules_init_cmd_word(rules);
	rules_init_command(rules);
	rules_init_complete_command(rules);
	rules_init_complete_commands(rules);
	rules_init_compound_command(rules);
	rules_init_compound_list(rules);
	rules_init_do_group(rules);
	rules_init_else_part(rules);
	rules_init_filename(rules);
	rules_init_fname(rules);
	rules_init_for_clause(rules);
	rules_init_function_body(rules);
	init_remaining_rules(rules);
}

static void	init_remaining_rules(t_rule *rules)
{
	rules_init_function_definition(rules);
	rules_init_here_end(rules);
	rules_init_if_clause(rules);
	rules_init_in(rules);
	rules_init_io_file(rules);
	rules_init_io_here(rules);
	rules_init_io_redirect(rules);
	rules_init_linebreak(rules);
	rules_init_list(rules);
	rules_init_name(rules);
	rules_init_newline_list(rules);
	rules_init_pattern_list(rules);
	rules_init_pipe_sequence(rules);
	rules_init_pipeline(rules);
	rules_init_program(rules);
	rules_init_redirect_list(rules);
	rules_init_separator_op(rules);
	rules_init_separator(rules);
	rules_init_sequential_sep(rules);
	rules_init_simple_command(rules);
	rules_init_subshell(rules);
	rules_init_term(rules);
	rules_init_until_clause(rules);
	rules_init_while_clause(rules);
	rules_init_wordlist(rules);
}
