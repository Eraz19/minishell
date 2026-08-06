/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_life_cycle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:14:50 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:14:51 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "sig.h"
#include "alias.h"
#include <stdlib.h>
#include <assert.h>	// DEBUG

void	env_init(t_params *params)
{
	assert(params != NULL);
	params->name = NULL;
	var_init(&params->variables);
	options_init(&params->options);
	specials_init(&params->specials);
	positionals_init_stack(&params->positionals_stack);
	functions_init(&params->functions);
	process_init(&params->processes);
	cmd_cache_init(&params->cmd_cache);
	fd_init(&params->fd_manager);
	alias_init(&params->alias);
}

void	env_init_subshell(t_params *params, bool async_no_job_ctrl)
{
	option_set(&params->options, OPT_INTERACTIVE, false);
	process_clear(&params->processes);
	fd_init_subshell(&params->fd_manager);
	sig_init_subshell(async_no_job_ctrl);
}

void	env_clear(t_params *params)
{
	var_clear(&params->variables);
	options_clear(&params->options);
	specials_clear(&params->specials);
	positionals_clear_stack(&params->positionals_stack);
	functions_clear(&params->functions);
	process_clear(&params->processes);
	cmd_cache_clear(&params->cmd_cache);
	fd_clear(&params->fd_manager, true);
	sig_clear();
	alias_clear(&params->alias);
}

void	env_free(t_params *params)
{
	assert(params != NULL);
	params->name = NULL;
	var_free(&params->variables);
	options_free(&params->options);
	specials_free(&params->specials);
	positionals_free_stack(&params->positionals_stack);
	functions_free(&params->functions);
	process_free(&params->processes);
	cmd_cache_free(&params->cmd_cache);
	fd_free(&params->fd_manager);
	sig_free();
	alias_free(&params->alias);
}
