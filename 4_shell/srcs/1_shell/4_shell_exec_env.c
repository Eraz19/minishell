#include "shell_priv.h"
#include "env.h"
#include "asm_stubs.h"
#include "expander.h"
#include "runner.h"
#include <stdlib.h>
# include "logs.h"		// DEBUG
#include <assert.h>	// DEBUG

#define ENV_NAME	"ENV"
#define POSIX_CIT_1	"POSIX 2.5.3: If the expanded value of ENV is not an "
#define POSIX_CIT_2	"absolute pathname, the results are unspecified"
#define IMPL		"skip ENV processing"

static inline bool	shell_ids_are_matching(void)
{
	uid_t	user_id;
	uid_t	effective_user_id;
	gid_t	group_id;
	gid_t	effective_group_id;

	user_id = ft_getuid();
	effective_user_id = ft_geteuid();
	group_id = ft_getgid();
	effective_group_id = ft_getegid();
	if (user_id == (uid_t)-1
		|| effective_user_id == (uid_t)-1
		|| group_id == (gid_t)-1
		|| effective_group_id == (gid_t)-1)
	{
		print_warn("unable to check user/group ids               => %sENV execution skipped%s\n", YELLOW, NC);
		return (false);
	}
	else if (user_id != effective_user_id || group_id != effective_group_id)
	{
		print_warn("real/effective user/group ids don't match    => %sENV execution skipped%s\n", YELLOW, NC);
		return (false);
	}
	return (true);
}

static inline t_error	shell_get_raw_env_path(
							bool *has_env,
							t_string *out_raw_env)
{
	t_error	err;

	*has_env = false;
	err = env_get_from_const(ENV_NAME, out_raw_env);
	if (err.type == ERR_VAR_NOT_FOUND)
	{
		print_warn("no ENV file to execute                       => %sENV execution skipped%s\n", YELLOW, NC);
		err.type = ERR_NO;
	}
	else if (err.type == ERR_NO && out_raw_env->len == 0)
	{
		string_free(out_raw_env);
		print_warn("no ENV file to execute                       => %sENV execution skipped%s\n", YELLOW, NC);
	}
	else if (err.type == ERR_NO)
		*has_env = true;
	return (err);
}

static inline t_error	shell_get_expanded_env_path(
							bool *has_env,
							t_string *out_env_path)
{
	t_string	raw_env;
	t_expansion	expansion;
	int			status;
	t_error		err;

	err = shell_get_raw_env_path(has_env, &raw_env);
	if (err.type || *has_env == false)
		return (err);
	status = -1;
	*has_env = false;
	err = expand_str(&expansion, &raw_env, &status, EXP_PARAM);
	if (err.type)
		return (string_free(&raw_env), err);
	else if (expansion.len > 1)
		print_warn("ENV expands to more than one field           => %sENV execution skipped%s\n", YELLOW, NC);
	else if (expansion.len == 0 || ((t_string *)expansion.data)[0].len == 0)
		print_warn("no ENV file to execute                       => %sENV execution skipped%s\n", YELLOW, NC);
	else
	{
		*has_env = true;
		expansion_take(&expansion, 0, out_env_path);
	}
	return (string_free(&raw_env), expansion_free(&expansion), err);
}

static inline t_error	shell_process_env(t_string *env_path)
{
	t_runner	*runner;
	t_error		err;

	err = shell_get_new_runner(&runner, SCAN_MODE_FILE, env_path->data);
	if (err.type)
		return (string_free(env_path), err);
	err = runner_run(runner);
	string_free(env_path);
	shell_destroy_last_instance();
	if (err.type == ERR_NO)
		print_pass("ENV file processed\n");
	return (err);
}

t_error	shell_exec_env(void)
{
	bool		is_interactive;
	bool		has_env;
	t_string	env_path;
	t_error		err;

	err = option_is_active(OPT_INTERACTIVE, &is_interactive);
	if (err.type)
		return (err);
	else if (is_interactive == false)
		return (print_warn("non-interactive mode                         => %sENV execution skipped%s\n", YELLOW, NC), err);
	else if (shell_ids_are_matching() == false)
		return (err);
	err = shell_get_expanded_env_path(&has_env, &env_path);
	if (err.type || has_env == false)
		return (err);
	if (env_path.data[0] != '/')
	{
		print_unspecified_behaviour(NULL, POSIX_CIT_1 POSIX_CIT_2, IMPL);
		string_free(&env_path);
		return (err);
	}
	return (shell_process_env(&env_path));
}
