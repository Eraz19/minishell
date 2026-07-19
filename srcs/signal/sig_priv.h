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
// TODO: ajouter doc pour dire que SIGKILL / SIGSTOP ne sont pas listés car POSIX dit que leur comportement est undefined dans trap
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

typedef struct s_sig_state
{
	bool			ignored_on_entry[SIG_ID_COUNT];
	t_sig_action	actions[SIG_ID_COUNT];
	t_sig_action	exit_action;
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
typedef struct s_signals
{
	volatile sig_atomic_t	has_pending;			// hint only
	volatile sig_atomic_t	pending[SIG_ID_COUNT];
	t_sig_state				state;
}	t_signals;

extern t_signals	g_signals;

// TODO: Si *édition de command* en cours => voir *extended description*
void	sigint_handler(void);

// helpers
int		sig_id_to_no(t_sig_id sig_id);
int		sig_no_to_id(int signo);
t_error	sig_parse_name(const char *name, int *out_signo, t_sig_id *out_sig_id);
t_error	sig_build_name(t_sig_id sig_id, t_string *out_name);

// ops
t_error	sig_install_shell_default_sigint(t_sig_action *sig_action);
t_error	sig_install_trap(t_sig_action *sig_action, int signo, t_string *cmd);
t_error	sig_install_default(t_sig_action *sig_action, int signo);
t_error	sig_install_ignore(t_sig_action *sig_action, int signo);
t_error	sig_build_output(t_sig_action *action, t_sig_id sig_id, t_string *out);

#endif
