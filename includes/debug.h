#ifndef DEBUG_H
# define DEBUG_H

# include <stdbool.h>
# include "action_type.h"
# include "symbols_type.h"
# include "lr_machine_type.h"
# include "ast_type.h"
# include "heredoc.h"
# include "logs.h"

const char	*bool_to_string(bool value);
const char	*action_type_to_string(t_action_type type);
const char	*symbol_to_string(t_symbol symbol);
void		debug_dump_rule(t_lr_machine *machine, size_t rule_id);
void		debug_dump_lr_state(t_lr_machine *machine, size_t lr_state_id);
void		debug_dump_cst_node(t_cst_node *node);
void		debug_dump_ast(t_ast_root *root);
void		debug_dump_heredoc_queue_item(t_heredoc_queue_item *item);

#endif
