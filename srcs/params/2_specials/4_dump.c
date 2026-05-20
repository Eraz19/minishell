#include "shell.h"
# include <stdio.h>

void	specials_dump(void)
{
	t_shell 	*shell;
	t_specials	*specials;

	printf("\nDUMP SPECIALS\n");
	shell = shell_get();
	if (!shell)
		error_print(NULL, "specials_dump()", ERR_SHELL_NOT_FOUND);
	specials = &shell->params.specials;
	if (specials->source)
		printf("SPECIAL source='%s'\n", specials->source);
	else
		printf("SPECIAL source=NULL\n");
	if (specials->zero)
		printf("SPECIAL 0='%s'\n", specials->zero);
	else
		printf("SPECIAL 0=NULL\n");
	printf("SPECIAL $=%ld\n", (long)specials->pid);
	printf("SPECIAL !=%ld\n", (long)specials->last_bg_pid);
	printf("SPECIAL ?=%i\n", specials->last_status);
}
