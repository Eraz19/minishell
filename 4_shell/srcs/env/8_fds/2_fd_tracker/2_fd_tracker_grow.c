#include "fd_tracker_priv.h"
#include "fd_tracker.h"
#include <limits.h>
#include <stdlib.h>
#include <stdint.h>

// @ret ERR_REDIRECTION
static inline t_error	fd_tracker_get_new_cap(
							size_t current_cap,
							size_t min_cap,
							size_t *out_cap)
{
	size_t	new_cap;

	if (current_cap == 0)
		new_cap = TRACKER_INITIAL_CAP;
	else
		new_cap = current_cap;
	while (new_cap < min_cap)
	{
		if (new_cap > INT_MAX / 2)
			return (redirect_print_error_all_fd_used());
		new_cap *= 2;
	}
	return (*out_cap = new_cap, error(ERR_NO));
}

static inline void	fd_tracker_update(
						t_fd_tracker *tracker,
						t_tracked_fd *new_data,
						size_t new_cap)
{
	size_t	item_size;
	size_t	item_to_copy;
	size_t	size_to_copy;
	size_t	size_to_init;

	item_size = sizeof(*tracker->data);
	if (tracker->data == NULL)
		item_to_copy = 0;
	else
		item_to_copy = tracker->cap;
	size_to_copy = item_to_copy * item_size;
	size_to_init = (new_cap * item_size) - size_to_copy;
	if (size_to_copy > 0)
		ft_memcpy(new_data, tracker->data, size_to_copy);
	ft_bzero(new_data + item_to_copy, size_to_init);
}

t_error	fd_tracker_grow(t_fd_tracker *tracker, size_t min_cap)
{
	t_tracked_fd	*new_data;
	size_t			new_cap;
	t_error			err;

	if (min_cap <= tracker->cap)
		return (error(ERR_NO));
	new_cap = 0;
	err = fd_tracker_get_new_cap(tracker->cap, min_cap, &new_cap);
	if (err.type)
		return (err);
	else if (new_cap > SIZE_MAX / sizeof(*tracker->data))
		return (redirect_print_error_all_fd_used());
	new_data = malloc(new_cap * sizeof(*tracker->data));
	if (!new_data)
		return (error_sys());
	fd_tracker_update(tracker, new_data, new_cap);
	if (tracker->data)
		free(tracker->data);
	tracker->data = new_data;
	tracker->cap = new_cap;
	return (err);
}
