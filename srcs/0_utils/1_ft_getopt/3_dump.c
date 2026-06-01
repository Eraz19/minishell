#include "ft_getopt.h"
# include "debug.h"
# include <stdio.h>

static void	getopt_dump_flag_with_arg(t_getopt_flag_with_arg *flag)
{
	size_t	i;

	printf("[%c%c", flag->sign, flag->flag);
	if (flag->arguments_are_optional)
		printf("[");
	else
		printf(" ");
	i = 0;
	while (flag->arguments_valids[i])
	{
		printf("%s", flag->arguments_valids[i]);
		if (flag->arguments_valids[i + 1])
			printf(" ");
		i++;
	}
	if (flag->arguments_are_optional)
		printf("]");
	printf("]\n");
}

void	getopt_dump_in(t_getopt_in *in)
{
	size_t	i;

	printf("\nGETOPT DUMP IN\n");
	printf("builtin_name=%s\n", in->builtin_name);
	printf("valid_minus_flags=%s\n", in->valid_minus_flags);
	printf("valid_plus_flags=%s\n", in->valid_plus_flags);
	i = 0;
	while (i < in->options_with_arg_count)
	{
		getopt_dump_flag_with_arg(&in->options_with_arg[i]);
		i++;
	}
	printf("options_with_arg_count=%zu\n", in->options_with_arg_count);
	printf("single_delimiter=%s\n", bool_to_string(in->single_delimiter));
	printf("ub_on_repeated_flags=%s\n", bool_to_string(in->ub_on_repeated_flags));
}

void	getopt_dump_out(t_getopt_out *out)
{
	size_t			i;
	t_getopt_option	*option;

	printf("\nGETOPT DUMP OUT\n");
	i = 0;
	while (i < out->options.len)
	{
		option = &((t_getopt_option *)out->options.data)[i];
		if (option->argument)
			printf("%c%c %s\n", option->sign, option->flag, option->argument);
		else
			printf("%c%c\n", option->sign, option->flag);
		i++;
	}
	printf("first_operand_index=%zu\n", out->first_operand_index);
}

void	getopt_dump_all(t_getopt_in *in, t_getopt_out *out)
{
	getopt_dump_in(in);
	getopt_dump_out(out);
}
