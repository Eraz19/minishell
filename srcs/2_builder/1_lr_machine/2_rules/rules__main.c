#include "rules__priv.h"
#include "libft.h"

static void	build_remaining_rules(t_rule *rules);

void	rules_init(t_rule *rules)
{
	ft_bzero(rules, RULE_COUNT * sizeof(*rules));
}

void	rules_build(t_rule *rules)
{
	rules_build_and_or(rules);
	rules_build_brace_group(rules);
	rules_build_case_clause(rules);
	rules_build_case_item_ns(rules);
	rules_build_case_item(rules);
	rules_build_case_list_ns(rules);
	rules_build_case_list(rules);
	rules_build_cmd_name(rules);
	rules_build_cmd_prefix(rules);
	rules_build_cmd_suffix(rules);
	rules_build_cmd_word(rules);
	rules_build_command(rules);
	rules_build_complete_command(rules);
	rules_build_complete_commands(rules);
	rules_build_compound_command(rules);
	rules_build_compound_list(rules);
	rules_build_do_group(rules);
	rules_build_else_part(rules);
	rules_build_filename(rules);
	rules_build_fname(rules);
	rules_build_for_clause(rules);
	rules_build_function_body(rules);
	rules_build_function_definition(rules);
	build_remaining_rules(rules);
}

static void	build_remaining_rules(t_rule *rules)
{
	rules_build_here_end(rules);
	rules_build_if_clause(rules);
	rules_build_in(rules);
	rules_build_io_file(rules);
	rules_build_io_here(rules);
	rules_build_io_redirect(rules);
	rules_build_linebreak(rules);
	rules_build_list(rules);
	rules_build_name(rules);
	rules_build_newline_list(rules);
	rules_build_pattern_list(rules);
	rules_build_pipe_sequence(rules);
	rules_build_pipeline(rules);
	rules_build_program(rules);
	rules_build_redirect_list(rules);
	rules_build_separator_op(rules);
	rules_build_separator(rules);
	rules_build_sequential_sep(rules);
	rules_build_simple_command(rules);
	rules_build_start(rules);
	rules_build_subshell(rules);
	rules_build_term(rules);
	rules_build_until_clause(rules);
	rules_build_while_clause(rules);
	rules_build_wordlist(rules);
}
