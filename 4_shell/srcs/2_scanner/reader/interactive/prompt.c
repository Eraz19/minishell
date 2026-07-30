#include "shell.h"
#include "env.h"
#include "expander.h"
#include "reader_interactive.h"

static t_error	ps1_append_history_index(t_string *out)
{
	t_error		err;
	t_history	*history;

	err = error(ERR_NO);
	history = shell_get_history();
	if (history == NULL)
	{
		(void)error_print(error(ERR_SHELL_NOT_FOUND), "reader", "PS1", NULL, NULL);
		if (!string_append_n(out, "!", 1))
			err = error_sys();
		return (err);
	}
	if (!string_append_format(out, "%u", (unsigned int)(history->list.len + 1)))
		err = error_sys();
	return (err);
}

static t_error	ps1_append_exclamation(t_string *out, const t_string *src, size_t *i)
{
	t_error	err;

	err = error(ERR_NO);
	if (src->data[*i] == '!' && src->data[*i + 1] == '!')
	{
		*i += 2;
		if (!string_append_n(out, "!", 1))
			err = error_sys();
	}
	else 
	{
		if (src->data[*i] == '!')
			err = ps1_append_history_index(out);
		else if (!string_append_n(out, &src->data[*i], 1))
			err = error_sys();
		*i += 1;
	}
	return (err);
}

static t_error	ps1_expand_exclamation(t_string *prompt)
{
	size_t		i;
	t_error		err;
	t_string	prompt_exp;

	i = 0;
	string_init(&prompt_exp, 0, NULL, 0);
	while (i < prompt->len)
	{
		err = ps1_append_exclamation(&prompt_exp, prompt, &i);
		if (err.type)
			return (string_free(&prompt_exp), err);
	}
	return (string_free(prompt), *prompt = prompt_exp, error(ERR_NO));
}

static const char	*prompt_mode_string(t_prompt_mode mode)
{
	if (mode == PROMPT_PS1)
		return ("PS1");
	else
		return ("PS2");
}

t_error	build_reader_prompt(t_string *out, t_prompt_mode mode)
{
	t_error		err;
	t_string	prompt;
	int			exit_status;

	string_init(out, 0, NULL, 0);
	err = env_get_from_const(prompt_mode_string(mode), &prompt);
	if (err.type == ERR_VAR_NOT_FOUND)
		return (error(ERR_NO));
	if (err.type)
		return (err);
	if (prompt.len == 0)
		return (string_free(&prompt), error(ERR_NO));
	if (mode == PROMPT_PS1)
		err = ps1_expand_exclamation(&prompt);
	if (err.type == ERR_NO)
		err = expand_str_merged(out, &prompt, &exit_status, EXP_PARAM);
	if (err.type)
	{
		(void)error_print(err, "scanner", prompt_mode_string(mode), NULL, NULL);
		return (string_free(out), *out = prompt, error(ERR_NO));
	}
	return (string_free(&prompt), error(ERR_NO));
}
