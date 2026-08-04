/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_logs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:09:26 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:09:27 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logs.h" // DEBUG
#include "history_priv.h"

void	history_load_start_logs(const char *func_name)
{
	print_title("%s()", func_name);
}

void	history_load_end_logs(const char *func_name)
{
	print_result("%s()", func_name);
}
