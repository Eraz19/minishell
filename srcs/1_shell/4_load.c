#include "shell_priv.h"
# include "logs.h"	// DEBUG

t_error	shell_load(t_shell_loading_options *options)
{
	t_error	err;

	print_title("shell_load()");
	err = params_load(&options->shell->params, options->argc, options->argv,
			options->envp);
	if (err.type == ERR_NO)
		err = history_load(&options->shell->history);
	if (err.type == ERR_NO)
		err = scanner_load(&options->shell->scanner,
				options->shell->params.specials.source.data);
	if (err.type == ERR_NO && options->build_parser_tables)
		err = builder_load(&options->shell->builder);
	if (err.type == ERR_NO)
		print_result("shell_load()");
	return (err);
}
