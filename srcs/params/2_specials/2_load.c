#include "asm_stubs.h"
#include "options.h"
#include "specials.h"
#include <stdlib.h>
# include "logs.h"	// DEBUG
# include <inttypes.h>	// DEBUG

// @ret ERR_OPT_INVALID
static t_error	specials_load_cmd_string(
	t_specials *specials,
	int argc,
	char **argv,
	size_t *operand_index)
{
	if ((size_t)argc < *operand_index + 1)
		return (error_print(error(ERR_OPT_INVALID),
			"-c needs an argument", NULL, NULL));
	specials->source = argv[(*operand_index)++];
	if ((size_t)argc >= *operand_index + 1)
		specials->zero = argv[(*operand_index)++];
	print_pass("mode initialized                       command_string (-c)\n");
	return (error(ERR_NO));
}

// @ret ERR_SHELL_NOT_FOUND / ERR_OPT_INVALID
static t_error	specials_load_source_and_zero(
	t_specials *specials,
	int argc,
	char **argv,
	size_t *operand_index)
{
	bool	is_cmd_string;
	bool	is_stdin;
	t_error	err;

	specials->source = NULL;
	specials->zero = argv[0];
	err = option_is_active(OPT_CMD_STRING, &is_cmd_string);
	if (err.type == ERR_NO)
		err = option_is_active(OPT_STDIN_INPUT, &is_stdin);
	if (err.type != ERR_NO)
		return (err);
	if (is_stdin)
		print_pass("mode initialized                       standard_input (-s)\n");	// TODO: return (error(ERR_NO))
	else if (is_cmd_string)
		err = specials_load_cmd_string(specials, argc, argv, operand_index);	// TODO: return (specials_load_cmd_string())
	else if ((size_t)argc >= *operand_index + 1)
	{
		print_pass("mode initialized                       command_file\n");
		specials->source = argv[(*operand_index)++];
		specials->zero = specials->source;
	}
	if (err.type == ERR_NO)
	{
		print_pass("zero initialized                       '%s'\n", specials->zero);
		print_pass("source initialized                     '%s'\n", specials->source);
	}
	return (err);
}

t_error	specials_load(
	t_specials *specials,
	int argc,
	char **argv,
	size_t *start_index)
{
	t_error	err;

	print_title("specials_load()");
	err = specials_load_source_and_zero(specials, argc, argv, start_index);
	if (err.type != ERR_NO)
		return (err);
	specials->last_bg_pid = -1;
	print_pass("last_bg_pid initialized                %jd\n", (intmax_t)specials->last_bg_pid);
	specials->last_status = EXIT_SUCCESS;
	print_pass("last_status initialized                %i\n", specials->last_status);
	specials->pid = ft_getpid();
	print_pass("pid initialized                        %jd\n", (intmax_t)specials->pid);
	print_result("specials_load()");
	return (error(ERR_NO));
}
