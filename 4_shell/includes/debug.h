#ifndef DEBUG_H
# define DEBUG_H

# include <stdbool.h>
# include "grammar_actions.h"
# include "grammar_symbols.h"
# include "lr_tables.h"
# include "parser_item_stack_type.h"
# include "ast.h"
# include "cmd.h"
# include "utils.h"
# include "logs.h"
# include "lexer.h"
# include "scanner.h"
# include "history.h"

const char	*bool_to_string(bool value);
const char	*action_type_to_string(t_action_type type);
const char	*cmd_type_to_string(t_cmd_type type);
const char	*scan_mode_to_string(t_scan_mode mode);
const char	*symbol_to_string(t_symbol symbol);
const char	*ast_command_type_to_string(t_ast_command_type type);
void		dump_rule(const t_lr_tables *tables, size_t rule_id);
void		dump_lr_state(const t_lr_tables *tables, size_t lr_state_id);
void		dump_parser_item_stack(t_parser_item_stack *stack);
void		dump_input_stack(t_lexer_input_stack *stack);
void		dump_context_stack(t_context_stack *stack);
void		dump_ast(t_ast_root *root);
void		dump_cst(t_cst_node *node);
void		dump_env(void);
void		dump_getopt_in(t_getopt_in *in);
void		dump_getopt_out(t_getopt_out *out);
void		dump_getopt_all(t_getopt_in *in, t_getopt_out *out);
void		dump_lexer_instance(t_lexer *lexer);
void		dump_scanner_instance(t_scanner *scanner);
void		dump_parser_instance(t_parser *parser);
void		dump_runner_instance(t_runner *runner);
void		dump_shell_instance(t_runner *runner, const char *caller);
void		dump_var_one(const char *name);
void		history_load_start_logs(const char *func_name);
void		history_load_end_logs(const char *func_name);
void		success_history_adapter_add_log(t_history_adapter *history_adapter);
void		history_file_save_start_log(t_history_file *history_file);
void		history_file_save_end_log(t_history_file *history_file);
void		empty_history_file_load_log(void);
void		success_history_file_load_log(t_history_file *history_file);
void		history_load_file_path_from_logs(const char *path, const char *origin);
void		history_load_max_size_from_unset_logs(void);
void		history_load_max_size_from_invalid_logs(void);
void		history_load_max_size_from_logs(ssize_t max);

#endif
