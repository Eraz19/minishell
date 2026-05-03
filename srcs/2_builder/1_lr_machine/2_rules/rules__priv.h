#ifndef RULES__PRIV_H
# define RULES__PRIV_H

# include "parser.h"

void	rules_init_and_or(t_rule *rules);
void	rules_init_brace_group(t_rule *rules);
void	rules_init_case_clause(t_rule *rules);
void	rules_init_case_item(t_rule *rules);
void	rules_init_case_item_ns(t_rule *rules);
void	rules_init_case_list(t_rule *rules);
void	rules_init_case_list_ns(t_rule *rules);
void	rules_init_cmd_name(t_rule *rules);
void	rules_init_cmd_prefix(t_rule *rules);
void	rules_init_cmd_suffix(t_rule *rules);
void	rules_init_cmd_word(t_rule *rules);
void	rules_init_command(t_rule *rules);
void	rules_init_complete_command(t_rule *rules);
void	rules_init_complete_commands(t_rule *rules);
void	rules_init_compound_command(t_rule *rules);
void	rules_init_compound_list(t_rule *rules);
void	rules_init_do_group(t_rule *rules);
void	rules_init_else_part(t_rule *rules);
void	rules_init_filename(t_rule *rules);
void	rules_init_fname(t_rule *rules);
void	rules_init_for_clause(t_rule *rules);
void	rules_init_function_body(t_rule *rules);
void	rules_init_function_definition(t_rule *rules);
void	rules_init_here_end(t_rule *rules);
void	rules_init_if_clause(t_rule *rules);
void	rules_init_in(t_rule *rules);
void	rules_init_io_file(t_rule *rules);
void	rules_init_io_here(t_rule *rules);
void	rules_init_io_redirect(t_rule *rules);
void	rules_init_linebreak(t_rule *rules);
void	rules_init_list(t_rule *rules);
void	rules_init_name(t_rule *rules);
void	rules_init_newline_list(t_rule *rules);
void	rules_init_pattern_list(t_rule *rules);
void	rules_init_pipeline(t_rule *rules);
void	rules_init_pipe_sequence(t_rule *rules);
void	rules_init_program(t_rule *rules);
void	rules_init_redirect_list(t_rule *rules);
void	rules_init_sequential_sep(t_rule *rules);
void	rules_init_separator(t_rule *rules);
void	rules_init_separator_op(t_rule *rules);
void	rules_init_simple_command(t_rule *rules);
void	rules_init_start(t_rule *rules);
void	rules_init_subshell(t_rule *rules);
void	rules_init_term(t_rule *rules);
void	rules_init_until_clause(t_rule *rules);
void	rules_init_while_clause(t_rule *rules);
void	rules_init_wordlist(t_rule *rules);

#endif
