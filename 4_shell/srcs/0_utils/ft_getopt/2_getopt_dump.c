#include "ft_getopt.h"
# include "debug.h"
#include <stdio.h>

static void	ft_getopt_dump_flag_with_arg(t_getopt_flag_with_arg *flag)
{
	size_t	i;

	fprintf(stderr, "[%c%c", flag->sign, flag->flag);
	if (flag->arguments_are_optional)
		fprintf(stderr, "[");
	else
		fprintf(stderr, " ");
	i = 0;
	while (flag->arguments_valids[i])
	{
		fprintf(stderr, "%s", flag->arguments_valids[i]);
		if (flag->arguments_valids[i + 1])
			fprintf(stderr, " ");
		i++;
	}
	if (flag->arguments_are_optional)
		fprintf(stderr, "]");
	fprintf(stderr, "]\n");
}

void	dump_getopt_in(t_getopt_in *in)
{
	size_t	i;

	fprintf(stderr, "\nGETOPT DUMP IN\n");
	fprintf(stderr, "builtin_name=%s\n", in->builtin_name);
	fprintf(stderr, "valid_minus_flags=%s\n", in->valid_minus_flags);
	fprintf(stderr, "valid_plus_flags=%s\n", in->valid_plus_flags);
	i = 0;
	while (i < in->options_with_arg_count)
	{
		ft_getopt_dump_flag_with_arg(&in->options_with_arg[i]);
		i++;
	}
	fprintf(stderr, "options_with_arg_count=%zu\n", in->options_with_arg_count);
	fprintf(stderr, "single_delimiter=%s\n", bool_to_string(in->single_delimiter));
	fprintf(stderr, "ub_on_repeated_flags=%s\n", bool_to_string(in->ub_on_repeated_flags));
}

void	dump_getopt_out(t_getopt_out *out)
{
	size_t			i;
	t_getopt_option	*option;

	fprintf(stderr, "\nGETOPT DUMP OUT\n");
	i = 0;
	while (i < out->options.len)
	{
		option = &((t_getopt_option *)out->options.data)[i];
		if (option->argument)
			fprintf(stderr, "%c%c %s\n", option->sign, option->flag, option->argument);
		else
			fprintf(stderr, "%c%c\n", option->sign, option->flag);
		i++;
	}
	fprintf(stderr, "first_operand_index=%zu\n", out->first_operand_index);
}

void	dump_getopt_all(t_getopt_in *in, t_getopt_out *out)
{
	dump_getopt_in(in);
	dump_getopt_out(out);
}
