#include "history.h"
#include "history_priv.h"
#include "history_load_env.h"

void	history_init(t_history *history)
{
	*history = (t_history){0};
	history_list_init(&history->list);
	history_file_init(&history->file);
	history_adapter_init(&history->adapter);
	string_init(&history->current_input, 0, NULL, 0);
}

void	history_free(t_history *history)
{
	history_list_free(&history->list);
	history_file_free(&history->file);
	string_free(&history->current_input);
	history_adapter_free(&history->adapter);
}

t_error	history_load(t_history *history)
{
	ssize_t	max;

	history_load_start_logs(__func__);
	if (load_history_path_from_env(history).type)
		return (history->err);
	if (load_history_max_size_env(history).type)
		return (history->err);
	max = history->adapter.max;
	if (history_file_load(&history->file, &history->list, max).type)
		return (history->err);
	history_adapter_load(&history->adapter, &history->list);
	history_load_start_logs(__func__);
	return (history->err);
}
