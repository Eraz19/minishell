#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define PREFIX	"[TEST] "
#define YELLOW	"\033[0;33m"
#define NC		"\033[0m"

static void	test_print(const char *format, ...)
{
	va_list	args;

	va_start(args, format);
	fprintf(stderr, YELLOW PREFIX);
	vfprintf(stderr, format, args);
	fprintf(stderr, NC);
	va_end(args);
}

static void	print_argv(int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		test_print("argv[%i] => [%s]\n", i, argv[i]);
		i++;
	}
}

static void	print_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		test_print("envp[%i] => [%s]\n", i, envp[i]);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	test_print("----------------------------------\n");
	test_print("argc => %i\n", argc);
	test_print("----------------------------------\n");
	print_argv(argc, argv);
	test_print("----------------------------------\n");
	print_envp(envp);
	test_print("----------------------------------\n");
	if (argc < 2)
		return (0);
	return (atoi(argv[1]));
}
