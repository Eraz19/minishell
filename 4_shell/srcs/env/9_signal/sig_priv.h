#ifndef SIG_PRIV_H
# define SIG_PRIV_H

# include "sig_action.h"
# include "error.h"
# include <stddef.h>
# include <signal.h>

/*
** POSIX IEEE Std 1003.1-2024: Shell Command Language: trap
** - "The condition can be EXIT, 0 (equivalent to EXIT), or a signal specified
**    using a symbolic name, without the SIG prefix"
**
** POSIX IEEE Std 1003.1-2024: XBD 14: Headers: <signal.h>
** - "SIGRTMIN Minimum realtime signal number."
** - "SIGRTMAX Maximum realtime signal number."
** - "need not be constant expressions"
**
** POSIX trap conditions are specified through symbolic signal names, while
** POSIX realtime signals are exposed as the SIGRTMIN..SIGRTMAX numeric range.
** Since this enum is a compile-time list of named signal macros, and since the
** realtime range bounds cannot portably be used as enum constants, realtime
** signals are not supported.
*/
/**
 * @enum e_sig_id
 * @brief Internal dense identifier for supported non-realtime signal names.
 *
 * @note The enum contents depend on signal macros exposed by @c <signal.h>.
 * @note @c SIG_EXIT_ID represents the @c EXIT / @c 0 trap condition and is
 *       not a real signal number.
 */
typedef enum e_sig_id
{
#ifdef SIGHUP
	SIGHUP_ID,
#endif
#ifdef SIGINT
	SIGINT_ID,
#endif
#ifdef SIGQUIT
	SIGQUIT_ID,
#endif
#ifdef SIGILL
	SIGILL_ID,
#endif
#ifdef SIGTRAP
	SIGTRAP_ID,
#endif
#ifdef SIGABRT
	SIGABRT_ID,
#endif
#ifdef SIGIOT
	SIGIOT_ID,
#endif
#ifdef SIGEMT
	SIGEMT_ID,
#endif
#ifdef SIGFPE
	SIGFPE_ID,
#endif
#ifdef SIGBUS
	SIGBUS_ID,
#endif
#ifdef SIGSEGV
	SIGSEGV_ID,
#endif
#ifdef SIGSYS
	SIGSYS_ID,
#endif
#ifdef SIGPIPE
	SIGPIPE_ID,
#endif
#ifdef SIGALRM
	SIGALRM_ID,
#endif
#ifdef SIGTERM
	SIGTERM_ID,
#endif
#ifdef SIGURG
	SIGURG_ID,
#endif
#ifdef SIGTSTP
	SIGTSTP_ID,
#endif
#ifdef SIGCONT
	SIGCONT_ID,
#endif
#ifdef SIGCHLD
	SIGCHLD_ID,
#endif
#ifdef SIGTTIN
	SIGTTIN_ID,
#endif
#ifdef SIGTTOU
	SIGTTOU_ID,
#endif
#ifdef SIGIO
	SIGIO_ID,
#endif
#ifdef SIGXCPU
	SIGXCPU_ID,
#endif
#ifdef SIGXFSZ
	SIGXFSZ_ID,
#endif
#ifdef SIGVTALRM
	SIGVTALRM_ID,
#endif
#ifdef SIGPROF
	SIGPROF_ID,
#endif
#ifdef SIGWINCH
	SIGWINCH_ID,
#endif
#ifdef SIGINFO
	SIGINFO_ID,
#endif
#ifdef SIGUSR1
	SIGUSR1_ID,
#endif
#ifdef SIGUSR2
	SIGUSR2_ID,
#endif
// Linux implementation-defined signals
#ifdef SIGPOLL
	SIGPOLL_ID,
#endif
#ifdef SIGCLD
	SIGCLD_ID,
#endif
#ifdef SIGPWR
	SIGPWR_ID,
#endif
#ifdef SIGLOST
	SIGLOST_ID,
#endif
#ifdef SIGSTKFLT
	SIGSTKFLT_ID,
#endif
#ifdef SIGUNUSED
	SIGUNUSED_ID,
#endif
// Free BSD implementation-defined signals
#ifdef SIGTHR
	SIGTHR_ID,
#endif
#ifdef SIGLIBRT
	SIGLIBRT_ID,
#endif
// Solaris implementation-defined signals
#ifdef SIGWAITING
	SIGWAITING_ID,
#endif
#ifdef SIGLWP
	SIGLWP_ID,
#endif
#ifdef SIGFREEZE
	SIGFREEZE_ID,
#endif
#ifdef SIGTHAW
	SIGTHAW_ID,
#endif
#ifdef SIGCANCEL
	SIGCANCEL_ID,
#endif
	SIG_ID_COUNT,
	SIG_EXIT_ID
}	t_sig_id;

/**
 * @struct s_sig_state
 * @brief Stores installed trap state and entry-time signal policy.
 *
 * @var s_sig_state::ignored_on_entry Whether each signal was ignored when the
 *                                    shell loaded signal state.
 * @var s_sig_state::actions Installed action for each supported signal.
 * @var s_sig_state::exit_action Installed action for the @c EXIT / @c 0 trap.
 * @var s_sig_state::is_executing_exit_action Whether the @c EXIT action is
 *                                            currently running.
 */
typedef struct s_sig_state
{
	/** @brief Whether each signal was ignored when signal state was loaded. */
	bool			ignored_on_entry[SIG_ID_COUNT];
	/** @brief Installed action for each supported signal. */
	t_sig_action	actions[SIG_ID_COUNT];
	/** @brief Installed action for the @c EXIT / @c 0 trap. */
	t_sig_action	exit_action;
	/** @brief Whether the @c EXIT action is currently running. */
	bool			is_executing_exit_action;
}	t_sig_state;

/*
** POSIX IEEE Std 1003.1-2024: XSH 2.4.3: Signal Actions:
** "The behavior is undefined if the signal handler refers to any object other
**  than errno with static or thread storage duration that is not a lock-free
**  atomic object, and not a non-modifiable object [...] other than by assigning
**  a value to an object declared as volatile sig_atomic_t, unless the previous
**  modification (if any) to the object happens before the signal handler is
**  called and the return from the signal handler happens before the next
**  modification (if any) to the object"
**
** Therefore:
** - has_pending and table[sig_id] can be assigned by the handler because they
**   are volatile sig_atomic_t objects.
** - pending_min / pending_max optimization can NOT be used to speed up the
**   lookup because maintaining them would require a read-compare-write sequence
**   in the handler, not a simple volatile sig_atomic_t assignment.
** - state is not accessed (read or write) by the signal handler.
*/
/**
 * @struct s_signals
 * @brief Global signal state shared by the shell and async signal handler.
 *
 * @var s_signals::has_pending Async-safe flag set when any signal is pending.
 * @var s_signals::pending Async-safe per-signal pending table.
 * @var s_signals::state Shell-side signal state, never accessed from the
 *                       signal handler.
 */
typedef struct s_signals
{
	/** @brief Async-safe flag set when any signal is pending. */
	volatile sig_atomic_t	has_pending;
	/** @brief Async-safe per-signal pending table. */
	volatile sig_atomic_t	pending[SIG_ID_COUNT];
	/** @brief Shell-side signal state, never accessed from the handler. */
	t_sig_state				state;
	t_sig_state				snapshot;
	bool					trap_with_operand_has_been_executed;
}	t_signals;

extern t_signals	g_signals;

/* ************************************************************************* */
/*                                  HELPERS                                  */
/* ************************************************************************* */

/**
 * @brief Build the symbolic trap name for @p sig_id.
 *
 * @note @p out_name is initialized by the function.
 *
 * @param sig_id Internal signal identifier to render.
 * @param out_name Destination @ref t_string (borrowed, initialized by the
 *                 function).
 * @return @c ERR_NO, @c ERR_INTERNAL or @c ERR_LIBC.
 */
t_error	sig_build_name(t_sig_id sig_id, t_string *out_name);

/**
 * @brief Convert an internal signal id to its platform signal number.
 *
 * @param sig_id Internal signal identifier to convert.
 * @return The matching signal number, or @c -1 when @p sig_id is unknown.
 */
int		sig_id_to_no(t_sig_id sig_id);

/**
 * @brief Convert a platform signal number to its internal signal id.
 *
 * @param signo Platform signal number to convert.
 * @return The matching @ref t_sig_id as an @c int, or @c -1 when @p signo is
 *         unknown.
 */
int		sig_no_to_id(int signo);

/**
 * @brief Parse a trap condition name or supported numeric signal.
 *
 * @param name Trap condition without the @c SIG prefix, or a supported numeric
 *             signal C-string (borrowed, read-only).
 * @param out_signo Destination receiving the platform signal number (borrowed).
 * @param out_sig_id Destination receiving the internal signal id (borrowed).
 * @return @c ERR_NO or @c ERR_VAR_INVALID_NAME.
 */
t_error	sig_parse_name(const char *name, int *out_signo, t_sig_id *out_sig_id);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @brief Build one re-input-safe @c trap output line for an action.
 *
 * @note @p out is initialized by the function and must be released by the
 *       caller with @ref string_free().
 *
 * @param action Signal action to serialize (borrowed, read-only).
 * @param sig_id Signal or @c EXIT condition to print.
 * @param out Destination @ref t_string (borrowed, initialized by the function).
 * @return @c ERR_NO, @c ERR_INTERNAL or @c ERR_LIBC.
 */
t_error	sig_build_output(t_sig_action *action, t_sig_id sig_id, t_string *out);

// TODO: doc
// @ret ERR_INTERNAL
t_error	sig_get_printable_state(t_sig_state **out_sig_state_ptr);

/**
 * @brief Install the default action for @p signo.
 *
 * @param sig_action Stored action updated on success (borrowed).
 * @param signo Platform signal number to install.
 * @return @c ERR_NO, @c ERR_INTERNAL or @c ERR_LIBC.
 */
t_error	sig_install_default(t_sig_action *sig_action, int signo);

/**
 * @brief Install the ignored action for @p signo.
 *
 * @param sig_action Stored action updated on success (borrowed).
 * @param signo Platform signal number to ignore.
 * @return @c ERR_NO or @c ERR_LIBC.
 */
t_error	sig_install_ignore(t_sig_action *sig_action, int signo);

/**
 * @brief Install the shell default @c SIGINT behavior.
 *
 * @param sig_action Stored @c SIGINT action updated on success (borrowed).
 * @return @c ERR_NO, @c ERR_INTERNAL or @c ERR_LIBC.
 */
t_error	sig_install_shell_default_sigint(t_sig_action *sig_action);

/**
 * @brief Install a trapped action for @p signo.
 *
 * @param sig_action Stored action updated on success (borrowed).
 * @param signo Platform signal number to trap.
 * @param cmd Trap command @ref t_string (ownership taken by signal).
 * @return @c ERR_NO or @c ERR_LIBC.
 */
t_error	sig_install_trap(t_sig_action *sig_action, int signo, t_string *cmd);

// TODO: doc
void	sig_snapshot(void);

#endif
