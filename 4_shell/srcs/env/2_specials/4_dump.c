#include "shell.h"
# include <stdio.h>

void	specials_dump(void)
{
	t_shell 	*shell;
	t_specials	*specials;

	fprintf(stderr, "\nDUMP SPECIALS\n");
	shell = shell_get();
	if (!shell)
		error_print(error(ERR_SHELL_NOT_FOUND), "specials_dump()", NULL, NULL);
	specials = &shell->params.specials;
	if (specials->source.len > 0)
		fprintf(stderr, "SPECIAL source='%s'\n", specials->source.data);
	else
		fprintf(stderr, "SPECIAL source=NULL\n");
	if (specials->zero.len > 0)
		fprintf(stderr, "SPECIAL 0='%s'\n", specials->zero.data);
	else
		fprintf(stderr, "SPECIAL 0=NULL\n");
	fprintf(stderr, "SPECIAL $=%jd\n", (intmax_t)specials->pid);
	fprintf(stderr, "SPECIAL !=%jd\n", (intmax_t)specials->last_bg_pid);
	fprintf(stderr, "SPECIAL ?=%i\n", specials->last_status);
}
