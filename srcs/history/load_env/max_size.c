#include "params.h"
#include "history_load_env.h"
#include "history_load_env_priv.h"

void	load_max_size_unset_value(t_history *history)
{
	history->adapter.max = -1;
	history_load_max_size_from_unset_logs();
}

void	load_max_size_invalid_value(t_history *history)
{
	history->adapter.max = -1;
	history_load_max_size_from_invalid_logs();
}

void	load_max_size_out_of_range_value(t_history *history)
{
	history_load_max_size_from_out_of_range_logs(history->adapter.max);
	history->adapter.max = 128;
}

t_error	load_history_max_size_env(t_history *history)
{
	long		max;
	t_string	max_str;

	history->err = params_get_from_const("HISTSIZE", &max_str);
	if (history->err.type && history->err.type != ERR_VAR_NOT_FOUND)
		return (history->err);
	if (history->err.type == ERR_VAR_NOT_FOUND || max_str.len == 0)
		load_max_size_unset_value(history);
	else if (!parse_long(max_str.data, &max))
		load_max_size_invalid_value(history);
	else
	{
		history->adapter.max = (ssize_t)max;
		if (max >= 0 && max < 128)
			load_max_size_out_of_range_value(history);
		else
			history_load_max_size_from_logs(max);
	}
	string_free(&max_str);
	return (history->err = error(ERR_NO));
}
