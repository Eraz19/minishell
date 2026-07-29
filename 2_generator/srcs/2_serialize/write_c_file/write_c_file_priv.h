#ifndef WRITE_C_FILE_PRIV_H
# define WRITE_C_FILE_PRIV_H

# include "generator.h"
# include <stdbool.h>

// helpers

bool	generator_write_c_var_start(int c_fd, const char *var_def);
bool	generator_write_c_var_end(int c_fd);
bool	generator_write_brack_start(int c_fd);
bool	generator_write_brack_end(int c_fd);
bool	generator_write_brack_last(int c_fd);

// vars

bool	generator_write_c_rules(int c_fd, const t_lr_generator *gen);
bool	generator_write_c_actions(int c_fd, const t_lr_generator *gen);
bool	generator_write_c_gotos(int c_fd, const t_lr_generator *gen);
// TODO
bool	generator_write_c_expects(int c_fd, const t_lr_generator *gen);

#endif
