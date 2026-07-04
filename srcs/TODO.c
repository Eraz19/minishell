#include "error.h"
#include "expander_.h"
#include <stdbool.h>

/* ---------- TODO: shell ---------- */

t_error		shell_should_interrupt(void)
{
	// TODO
	return (error(ERR_INTERRUPTED));
}

/* ---------- TODO: runner/subshell ---------- */

// Voici les cas possibles
//	- EOI avant cmd_sub closing tokan.end == -1
//	- cmd_sub closing detected token.end == lexer_i du lexer interne
t_error	runner_find_cmd_sub_closing(t_token *out, t_string *input)
{
	// TODO
	(void)out;
	(void)input;
	return (error(ERR_NOT_IMPLEMENTED));
}

/* ---------- TODO: expander ---------- */
