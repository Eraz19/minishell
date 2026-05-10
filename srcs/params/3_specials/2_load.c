#include "shell.h"
#include "specials.h"
#include "asm_stubs.h"
#include <stdlib.h>

// Errors can be ERR_OPTION_INVALID
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
	return (ERR_NO);
}

// Errors can be ERR_SHELL_NOT_FOUND / ERR_OPTION_INVALID
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
		return (ERR_NO);
	else if ((size_t)argc >= *operand_index + 1)
	{
		specials->source = argv[(*operand_index)++];
		specials->zero = specials->source;
	}
	return (ERR_NO);
}

t_error	specials_load(t_specials *specials, int argc, char **argv, size_t options_count)
{
	size_t	operand_index;
	t_shell	*shell;
	t_error	error;

	operand_index = options_count + 1;
	specials->last_bg_pid = -1;
	specials->last_status = EXIT_SUCCESS;
	shell = shell_get();
	if (!shell)
		return (ERR_SHELL_NOT_FOUND);
	if (shell->params.parent_shell)
		specials->pid =
			((t_shell *)shell->params.parent_shell)->params.specials.pid;
	else
		specials->pid = ft_getpid();
	error = specials_load_source_and_zero(specials, argc, argv, &operand_index);
	if (error != ERR_NO)
		return (error);
	specials->positional_params = NULL;
	specials->positional_count = (size_t)argc - operand_index;
	if (specials->positional_count > 0)
		specials->positional_params = argv + operand_index;
	return (ERR_NO);
}
