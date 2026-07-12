#ifndef JOB_H
# define JOB_H

# include "libft.h"
# include "ast.h"

/* ---------- LATER (when required functions will be available) ----------*/

typedef enum e_job_status
{
	JOB_RUNNING,
	JOB_STOPPED,
	JOB_DONE
}	t_job_status;

typedef struct s_job
{
	size_t			job_id;
	t_job_status	status;
	pid_t			pgid;
	t_vector		process_list;	// t_vector of t_process
	t_ast_command	cmd;
}	t_job;

/* ---------------------------------------------------------------------- */

#endif
