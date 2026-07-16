#ifndef CMD_SUB
# define CMD_SUB

# include "error.h"
# include "scanner.h"
# include "builder.h"
# include <stddef.h>

// TODO: scanner
t_error	scanner_cmd_sub_init(const t_scanner *main_scanner, t_scanner *cmd_sub_scanner);
t_error	scanner_cmd_sub_free(t_scanner *cmd_sub_scanner);

t_error	builder_cmd_sub_init(const t_builder *main_builder, t_builder *cmd_sub_builder);
t_error	builder_cmd_sub_free(t_builder *cmd_sub_builder);

// API
t_error	cmd_sub_find_end(size_t *out_token_id);

#endif
