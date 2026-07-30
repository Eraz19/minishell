#include "shell.h"
#include "error.h"
#include "history.h"
#include "history_priv.h"

t_error	history_save_entry(void)
{
	t_history	*history;
	
	history = shell_get_history();
	if (history->current_input.len == 0)
		return (error(ERR_NO));
	if (history->current_input.data[history->current_input.len - 1] == '\n')
	{
		history->current_input.data[history->current_input.len - 1] = '\0';
		history->current_input.len--;
	}
	if (history->current_input.len == 0)
		return (error(ERR_NO));
	history->err = history_list_push(&history->list, &history->current_input);
	if (history->err.type)
		return (history->err);
	string_init(&history->current_input, 0, NULL, 0);
	add_to_readline_history(&history->adapter, &history->list, 1);
	return (history->err);
}

t_error	history_append_to_entry(t_string *entry)
{
	t_history	*history;

	history = shell_get_history();
	if (!string_append(&history->current_input, entry))
		return (requalify_history_error(history->err = error_sys()));
	return (history->err);
}

t_error	history_save(void)
{
	t_history	*history;

	history = shell_get_history();
	if (build_saving_file_content(history, history->file.loaded_count).type)
		return (history->err = requalify_history_error(history->err));
	history->err = requalify_history_error(write_history_file(&history->file));
	return (history->err);
}
