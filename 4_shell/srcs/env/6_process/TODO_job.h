/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TODO_job.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:11:55 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 15:09:07 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TODO_JOB_H
# define TODO_JOB_H

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
