#include "generator_actions_priv.h"
#include "libft.h"
#include <unistd.h>

#define CONFLICT_PREFIX	"generator: ambiguous grammar: "
#define SHIFT			"SHIFT"
#define REDUCE			"REDUCE"
#define ACCEPT			"ACCEPT"
#define CONFLICT_SUFFIX	" conflict\n"

static inline bool	action_report_conflict(
						const t_action *action,
						t_action_type new_action_type)
{
	ssize_t	osef;

	osef = write(STDERR_FILENO, CONFLICT_PREFIX, str_len(CONFLICT_PREFIX));
	if (action->type == ACTION_SHIFT)
		osef = write(STDERR_FILENO, SHIFT, str_len(SHIFT));
	else if (action->type == ACTION_REDUCE)
		osef = write(STDERR_FILENO, REDUCE, str_len(REDUCE));
	else if (action->type == ACTION_ACCEPT)
		osef = write(STDERR_FILENO, ACCEPT, str_len(ACCEPT));
	osef = write(STDERR_FILENO, "-", 1);
	if (new_action_type == ACTION_SHIFT)
		osef = write(STDERR_FILENO, SHIFT, str_len(SHIFT));
	else if (new_action_type == ACTION_REDUCE)
		osef = write(STDERR_FILENO, REDUCE, str_len(REDUCE));
	else if (new_action_type == ACTION_ACCEPT)
		osef = write(STDERR_FILENO, ACCEPT, str_len(ACCEPT));
	osef = write(STDERR_FILENO, CONFLICT_SUFFIX, str_len(CONFLICT_SUFFIX));
	(void)osef;
	return (true);
}

bool	action_is_conflict(
			const t_action *action,
			t_action_type new_action_type,
			size_t new_payload)
{
	if (action->type != ACTION_ERROR
		&& (action->type != new_action_type || action->payload != new_payload))
		return (action_report_conflict(action, new_action_type));
	return (false);
}
