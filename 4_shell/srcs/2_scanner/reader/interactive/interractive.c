#include "reader_interactive.h"
#include "reader_interactive_priv.h"

t_error	read_interactive(t_string *out, t_prompt_mode mode, size_t max_retry)
{
	t_error		err;
	t_string	prompt;

	err = build_reader_prompt(&prompt, mode);
	if (err.type)
		return (err);
	(void)string_init(out, 0, NULL, 0);
	while (out->len < 2)
	{
		string_free(out);
		err = read_line(out, prompt.data, max_retry);
		if (err.type)
			break ;
		if (mode == PROMPT_PS2)
			break ;
	}
	if (err.type)
		return (string_free(out), string_free(&prompt), err);
	return (string_free(&prompt), err);
}
