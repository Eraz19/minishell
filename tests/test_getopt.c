#include "ft_getopt.h"
#include <stdlib.h>
#include <stdio.h>

void	shell_exit(t_error error)
{
	exit((int)error);
}

// TODO: automatic parsing of synopsis ?

/*
ccc \
-Ilibft \
-Iincludes \
-Isrcs/3_builder/1_lr_machine \
-Isrcs/3_builder/1_lr_machine/1_hooks \
-Isrcs/3_builder/1_lr_machine/2_rules \
-Isrcs/3_builder/1_lr_machine/3_symbols \
-Isrcs/3_builder/1_lr_machine/4_first \
-Isrcs/3_builder/1_lr_machine/5_rule_state \
-Isrcs/3_builder/1_lr_machine/6_lr_state \
-Isrcs/3_builder/1_lr_machine/7_transition \
-Isrcs/3_builder/1_lr_machine/8_goto \
-Isrcs/3_builder/1_lr_machine/9_action \
-Isrcs/builtins \
-Isrcs/builtins/export \
-Isrcs/builtins/readonly \
-Isrcs/builtins/unset \
-Isrcs/params/1_options \
-Isrcs/params/2_specials \
-Isrcs/params/3_positionals \
-Isrcs/params/4_variables \
-Isrcs/params/4_variables/load \
-Isrcs/params/4_variables/load/1_envp \
-Isrcs/params/4_variables/load/2_mandatory \
-Isrcs/params/4_variables/load/2_mandatory/ft_getppid \
-Isrcs/params/4_variables/load/3_up \
libft/libft.a \
srcs/error.c \
srcs/debug.c \
srcs/ub.c \
srcs/1_shell/2_helpers.c \
srcs/0_posix_helpers/posix_write.c \
srcs/0_utils/1_ft_getopt/\*.c \
tests/test_getopt.c \
-o tests/test_getopt
*/

/*
TESTS: [-a] [–b] [-c arg] [-d[arg]]
OK:
	./tests/test_getopt "-a" "-b" "-d" "-c" "arg"
	./tests/test_getopt "-ab"
	./tests/test_getopt "-abc" "arg"
	./tests/test_getopt "-abd"
	./tests/test_getopt "-abd" "arg"
	./tests/test_getopt "-abdarg"
ERROR:
	./tests/test_getopt "-azb"
	./tests/test_getopt "-adb"
	./tests/test_getopt "-acb" "arg"
	./tests/test_getopt "-adc" "arg"
	./tests/test_getopt "-abc"
	./tests/test_getopt "-abzd"
	./tests/test_getopt "-abzdarg"
	./tests/test_getopt "-abzc" "arg"
*/

#define OPT_WITH_ARGS_COUNT	2

static t_getopt_flag_with_arg	option_c(void)
{
	static const char	*args[] = {"arg", NULL};

	return ((t_getopt_flag_with_arg)
	{
		.sign = '-',
		.flag = 'c',
		.arguments_are_optional = false,
		.arguments_valids = args
	});
}

static t_getopt_flag_with_arg	option_d(void)
{
	static const char	*args[] = {"arg", NULL};

	return ((t_getopt_flag_with_arg)
	{
		.sign = '-',
		.flag = 'd',
		.arguments_are_optional = true,
		.arguments_valids = args
	});
}

static bool	build_in(t_getopt_in *in)
{
	in->builtin_name = "builtin";
	in->valid_minus_flags = "ab";
	in->valid_plus_flags = NULL;
	in->options_with_arg = malloc(OPT_WITH_ARGS_COUNT * sizeof(*in->options_with_arg));
	if (!in->options_with_arg)
		return (false);
	in->options_with_arg[0] = option_c();
	in->options_with_arg[1] = option_d();
	in->options_with_arg_count = OPT_WITH_ARGS_COUNT;
	in->single_delimiter = true;
	in->ub_on_repeated_flags = false;
	return (true);
}

int	main(int argc, char **argv)
{
	t_getopt_in		in;
	t_error			error;
	t_getopt_out	out;

	if (!build_in(&in))
		return (EXIT_FAILURE);
	error = ft_getopt(argc, argv, &in, &out);
	if (error == ERR_NO)
		getopt_dump_all(&in, &out);
	free(in.options_with_arg);
	vector_free(&out.options, NULL);
	return ((int)error);
}
