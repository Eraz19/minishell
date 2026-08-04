/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_file_logs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:08:32 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:08:33 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logs.h"	// DEBUG
#include "history_file.h"

void	history_file_save_start_log(t_history_file *history_file)
{
	if (history_file->path.len == 0)
		print_warn("[HISTORY] History disabled: %sskipping save%s\n", YELLOW, NC);
	else if (history_file->content.len == 0)
		print_warn("[HISTORY] History empty: %sskipping save%s\n", YELLOW, NC);
}

void	history_file_save_end_log(t_history_file *history_file)
{
	if (history_file->err.type == ERR_NO)
		print_pass("[HISTORY] History saved to = %s%s%s\n", BLUE, history_file->path.data, NC);
}

void	empty_history_file_load_log(void)
{
	print_warn("entries loaded from history file       %s0%s\n", YELLOW, NC);
}

void	success_history_file_load_log(t_history_file *history_file)
{
	print_pass("entries loaded from history file       %i\n", (int)history_file->loaded_count);
}
