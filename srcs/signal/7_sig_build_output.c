#include "sig_priv.h"
#include "utils.h"

static inline t_error	sig_append_action(t_sig_action *action, t_string *out)
{
	t_string	serialized_cmd;
	t_error		err;


	if (action->type == SIG_DEFAULT)
	{
		if (!string_append_n(out, "-", 1))
			return (error_sys());
	}
	else if (action->type == SIG_IGNORED)
	{
		if (!string_append_n(out, "''", 2))
			return (error_sys());
	}
	else
	{
		err = serialize(action->cmd.data, &serialized_cmd);
		if (err.type)
			return (err);
		else if (!string_append(out, &serialized_cmd))
			return (err = error_sys(), string_free(&serialized_cmd), err);
		string_free(&serialized_cmd);
	}
	return (error(ERR_NO));
}

static inline t_error	sig_append_condition(t_sig_id sig_id, t_string *out)
{
	t_string	name;
	t_error		err;
	
	if (sig_id == SIG_EXIT_ID)
	{
		if (!string_append_n(out, "EXIT", -1))
			return (error_sys());
		return (error(ERR_NO));
	}
	err = sig_build_name(sig_id, &name);
	if (err.type)
		return (err);
	if (!string_append(out, &name))
		err = error_sys();
	string_free(&name);
	return (err);
}

t_error	sig_build_output(t_sig_action *action, t_sig_id sig_id, t_string *out)
{
	t_error	err;

	if (!string_init(out, 0, "trap -- ", -1))
		return (error_sys());
	err = sig_append_action(action, out);
	if (err.type)
		return (string_free(out), err);
	if (!string_append_n(out, " ", 1))
		return (err = error_sys(), string_free(out), err);
	err = sig_append_condition(sig_id, out);
	if (err.type)
		return (string_free(out), err);
	if (!string_append_n(out, "\n", 1))
		return (err = error_sys(), string_free(out), err);
	return (err);
}
