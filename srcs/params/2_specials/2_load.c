#include "shell.h"
#include "specials.h"
#include "asm_stubs.h"
#include <stdlib.h>
# include "logs.h"	// TODO: tmp debug
# include <inttypes.h>	// TODO: tmp debug

// @ret ERR_OPTION_INVALID
static t_error	specials_load_cmd_string(
	t_specials *specials,
	int argc,
	char **argv,
	size_t *operand_index)
{
	if ((size_t)argc < *operand_index + 1)
	{
		error_print(NULL, "-c needs an argument", ERR_OPTION_INVALID);
		return (ERR_OPTION_INVALID);
	}
	specials->source = argv[(*operand_index)++];
	if ((size_t)argc >= *operand_index + 1)
		specials->zero = argv[(*operand_index)++];
	print_pass("command_string (-c) mode initialized\n");
	print_pass("zero set to              '%s'\n", specials->zero);
	print_pass("source set to            '%s'\n", specials->source);
	return (ERR_NO);
}

// @ret ERR_SHELL_NOT_FOUND / ERR_OPTION_INVALID
static t_error	specials_load_source_and_zero(
	t_specials *specials,
	int argc,
	char **argv,
	size_t *operand_index)
{
	specials->source = NULL;
	specials->zero = argv[0];
	if (option_is_active(OPT_CMD_STRING))
		return (specials_load_cmd_string(specials, argc, argv, operand_index));
	else if (option_is_active(OPT_STDIN_INPUT))
	{
		print_pass("standard_input (-s) mode initialized\n");
		// return (ERR_NO);
	}
	else if ((size_t)argc >= *operand_index + 1)
	{
		print_pass("command_file mode initialized\n");
		specials->source = argv[(*operand_index)++];
		specials->zero = specials->source;
	}
	print_pass("zero set to              '%s'\n", specials->zero);
	print_pass("source set to            '%s'\n", specials->source);
	return (ERR_NO);
}

t_error	specials_load(
	t_specials *specials,
	int argc,
	char **argv,
	size_t *start_index)
{
	t_shell	*shell;
	t_error	error;

	print_title("specials_load()");
	error = specials_load_source_and_zero(specials, argc, argv, start_index);
	if (error != ERR_NO)
		return (error);
	specials->last_bg_pid = -1;
	print_pass("last_bg_pid set to       %jd\n", (intmax_t)specials->last_bg_pid);
	specials->last_status = EXIT_SUCCESS;
	print_pass("last_status set to       %i\n", specials->last_status);
	shell = shell_get();
	if (!shell)
		return (ERR_SHELL_NOT_FOUND);
	if (shell->params.parent_shell)
		specials->pid =
			((t_shell *)shell->params.parent_shell)->params.specials.pid;
	else
		specials->pid = ft_getpid();
	print_pass("pid set to               %jd\n", (intmax_t)specials->pid);
	print_result("specials_load()");
	return (ERR_NO);
}
