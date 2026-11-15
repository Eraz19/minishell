/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_action.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:13:11 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:13:12 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_ACTION_H
# define SIG_ACTION_H

# include "libft.h"

typedef enum e_sig_action_type
{
	SIG_DEFAULT,
	SIG_IGNORED,
	SIG_TRAPPED
}	t_sig_action_type;

typedef struct s_sig_action
{
	t_sig_action_type	type;
	t_string			cmd;
}	t_sig_action;

void	sig_action_init(t_sig_action *action);
void	sig_action_free(t_sig_action *action);

#endif
