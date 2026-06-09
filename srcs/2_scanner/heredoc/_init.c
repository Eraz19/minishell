/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 18:42:35 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/05 19:35:38 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__heredoc.h"

void	heredoc_init(t_heredoc *state)
{
	*(state) = (t_heredoc){0};
	here_queue_init(&state->queue);
}

void	heredoc_free(t_heredoc *state)
{
	here_queue_free(&state->queue);
	*(state) = (t_heredoc){0};
}

void	heredoc_load(t_heredoc *state, bool is_tty)
{
	state->is_tty = is_tty;
}

void	heredoc_reset(t_heredoc *state)
{
	bool	is_tty;

	is_tty = state->is_tty;
	heredoc_free(state);
	heredoc_init(state);
	state->is_tty = is_tty;
}
