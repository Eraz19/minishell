#ifndef SYMBOLS_H
# define SYMBOLS_H

# include "builder.h"

void	symbols_build_nullables_table(t_lr_machine *machine);
bool	symbol_is_terminal(t_symbol symbol);
bool	symbol_is_non_terminal(t_symbol symbol);
bool	symbol_is_nullable(t_lr_machine *machine, t_symbol symbol);
bool	symbols_are_nullable(t_lr_machine *machine, t_symbol *symbols, size_t count);

#endif
