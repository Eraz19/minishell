/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __history.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 13:06:00 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/08 11:26:19 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __HISTORY_H
# define __HISTORY_H

# include "libft.h"
# include "__history_rl.h"
# include "__history_list.h"
# include "__history_file.h"

typedef struct s_history
{
	t_error			err;
	t_history_file	file;
	t_history_list	list;
	t_history_rl	rl_history;
	t_buff			current_input;
}	t_history;

t_history	*shell_get_history(void);

#endif
