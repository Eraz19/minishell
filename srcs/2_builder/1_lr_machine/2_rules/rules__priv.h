#ifndef RULES__PRIV_H
# define RULES__PRIV_H

# include "builder.h"

void	rules_build_and_or(t_rule *rules);
void	rules_build_brace_group(t_rule *rules);
void	rules_build_case_clause(t_rule *rules);
void	rules_build_case_item(t_rule *rules);
void	rules_build_case_item_ns(t_rule *rules);
void	rules_build_case_list(t_rule *rules);
void	rules_build_case_list_ns(t_rule *rules);
void	rules_build_cmd_name(t_rule *rules);
void	rules_build_cmd_prefix(t_rule *rules);
void	rules_build_cmd_suffix(t_rule *rules);
void	rules_build_cmd_word(t_rule *rules);
void	rules_build_command(t_rule *rules);
void	rules_build_complete_command(t_rule *rules);
void	rules_build_complete_commands(t_rule *rules);
void	rules_build_compound_command(t_rule *rules);
void	rules_build_compound_list(t_rule *rules);
void	rules_build_do_group(t_rule *rules);
void	rules_build_else_part(t_rule *rules);
void	rules_build_filename(t_rule *rules);
void	rules_build_fname(t_rule *rules);
void	rules_build_for_clause(t_rule *rules);
void	rules_build_function_body(t_rule *rules);
void	rules_build_function_definition(t_rule *rules);
void	rules_build_here_end(t_rule *rules);
void	rules_build_if_clause(t_rule *rules);
void	rules_build_in(t_rule *rules);
void	rules_build_io_file(t_rule *rules);
void	rules_build_io_here(t_rule *rules);
void	rules_build_io_redirect(t_rule *rules);
void	rules_build_linebreak(t_rule *rules);
void	rules_build_list(t_rule *rules);
void	rules_build_name(t_rule *rules);
void	rules_build_newline_list(t_rule *rules);
void	rules_build_pattern_list(t_rule *rules);
void	rules_build_pipeline(t_rule *rules);
void	rules_build_pipe_sequence(t_rule *rules);
void	rules_build_program(t_rule *rules);
void	rules_build_redirect_list(t_rule *rules);
void	rules_build_sequential_sep(t_rule *rules);
void	rules_build_separator(t_rule *rules);
void	rules_build_separator_op(t_rule *rules);
void	rules_build_simple_command(t_rule *rules);
void	rules_build_start(t_rule *rules);
void	rules_build_subshell(t_rule *rules);
void	rules_build_term(t_rule *rules);
void	rules_build_until_clause(t_rule *rules);
void	rules_build_while_clause(t_rule *rules);
void	rules_build_wordlist(t_rule *rules);

#endif
