#ifndef DEBUG_H
# define DEBUG_H

# include <stdbool.h>
# include "action_type.h"
# include "symbols_type.h"
# include "lr_machine_type.h"
# include "parser_item_stack_type.h"
# include "ast.h"
# include "cmd_type.h"
# include "logs.h"
# include "lexer.h"

const char	*bool_to_string(bool value);
const char	*action_type_to_string(t_action_type type);
const char	*cmd_type_to_string(t_cmd_type type);
const char	*symbol_to_string(t_symbol symbol);
const char	*ast_command_type_to_string(t_ast_command_type type);
void		debug_dump_rule(t_lr_machine *machine, size_t rule_id);
void		debug_dump_lr_state(t_lr_machine *machine, size_t lr_state_id);
void		debug_dump_parser_item_stack(t_parser_item_stack *stack);
void		debug_dump_input_stack(t_lexer_input_stack *stack);
void		debug_dump_context_stack(t_context_stack *stack);
void		debug_dump_cst(t_cst_node *node);
void		debug_dump_ast(t_ast_root *root);

#endif
