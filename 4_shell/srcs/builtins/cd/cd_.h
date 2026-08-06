/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:40:38 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:40:39 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD__H
# define CD__H

# include "error.h"
# include "libft.h"

/**
 * @defgroup builtin_cd cd builtin
 * @brief POSIX.1-2024 cd: curpath construction (steps 1-6), logical
 *        canonicalization (step 7, -L only), PATH_MAX shortening
 *        (step 9), chdir + PWD/OLDPWD update (steps 8/10).
 *
 * Documented implementation-defined choices: no operand with HOME
 * unset OR empty is a diagnosed error (bash lane); with -P, when PWD
 * cannot be determined after a successful chdir, PWD keeps the
 * curpath value and the error is reported only under -e; consecutive
 * slashes (including leading ones) collapse to a single slash during
 * canonicalization.
 */

/**
 * @ingroup builtin_cd
 * @struct s_cd_args
 * @brief State of one cd invocation.
 *
 * @var s_cd_args::mode 'L' (logical, default) or 'P' (physical); the
 *                      last -L / -P option wins.
 * @var s_cd_args::ensure_pwd -e was given: an undeterminable PWD after
 *                            a successful -P chdir becomes an error.
 * @var s_cd_args::print The new PWD is written to stdout (a non-empty
 *                       CDPATH entry was used or the operand was '-').
 * @var s_cd_args::operand_index Index of the first operand in argv.
 * @var s_cd_args::curpath The pathname handed to chdir, owned.
 */
typedef struct s_cd_args
{
	char		mode;
	bool		ensure_pwd;
	bool		print;
	size_t		operand_index;
	t_string	curpath;
}	t_cd_args;

/**
 * @ingroup builtin_cd
 * @brief Reports whether @p path names an existing directory.
 *
 * @param path Pathname to test (borrowed, read-only).
 * @return true when stat() succeeds and the file is a directory.
 */
bool	cd_is_directory(const char *path);

/**
 * @ingroup builtin_cd
 * @brief Builds @c args->curpath from the @p dir operand (steps 2-6):
 *        kept as-is when absolute, dot-led or empty; otherwise the
 *        first CDPATH entry naming a directory provides the prefix
 *        (empty entry = current directory; a non-empty entry sets
 *        @c args->print).
 *
 * @param args Invocation state; curpath is replaced (borrowed).
 * @param dir Directory operand (borrowed, read-only).
 * @return @c ERR_SHELL_NOT_FOUND or @c ERR_LIBC from the CDPATH
 *         lookup or the copies, @c ERR_NO on success.
 */
t_error	cd_build_curpath(t_cd_args *args, const t_string *dir);

/**
 * @ingroup builtin_cd
 * @brief Canonicalizes @c args->curpath logically (step 7, -L):
 *        prepends PWD to a relative curpath, drops dot components,
 *        resolves each dot-dot after checking that the component it
 *        removes names a directory (diagnosed error otherwise, printed
 *        with the offending prefix), collapses slash runs.
 *
 * @param args Invocation state; curpath is replaced (borrowed).
 * @param utility argv[0], for diagnostics (borrowed, read-only).
 * @return @c ERR_VAR_NOT_FOUND if PWD is unset,
 *         @c ERR_SHELL_NOT_FOUND, @c ERR_LIBC (dot-dot validation
 *         failure, printed) on failure, @c ERR_NO on success.
 */
t_error	cd_canonicalize(t_cd_args *args, const char *utility);

/**
 * @ingroup builtin_cd
 * @brief Performs the directory change (steps 8-10): optional
 *        PATH_MAX shortening against PWD, chdir (failure printed with
 *        the pathname), then PWD update (-L: curpath; -P: getcwd,
 *        falling back to curpath, an error only under -e) and OLDPWD
 *        update from the previous PWD.
 *
 * @param args Invocation state (borrowed, read-only except curpath).
 * @param utility argv[0], for diagnostics (borrowed, read-only).
 * @return @c ERR_LIBC (chdir/getcwd failure, printed),
 *         @c ERR_VAR_READ_ONLY / @c ERR_VAR_INVALID_NAME /
 *         @c ERR_SHELL_NOT_FOUND from the variable updates,
 *         @c ERR_NO on success.
 */
t_error	cd_apply(t_cd_args *args, const char *utility);

t_error	cd_print_new(void);

#endif
