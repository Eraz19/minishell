/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_label.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:44:54 by adouieb           #+#    #+#             */
/*   Updated: 2026/04/09 16:48:55 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "prompt_label.h"

static t_user_name	get_user_name(void)
{
	t_i8	*user_name;

	user_name = getenv("USER");
	if (user_name == NULL)
		return (dstr_c(cstr("unknown_user")));
	else
		return (dstr_c(cstr(user_name)));
}

static t_host_name	get_user_host(void)
{
	t_i8	*user_host;

	user_host = getenv("HOSTNAME");
	if (user_host == NULL)
		return (dstr_c(cstr("unknown_host")));
	else
		return (dstr_c(cstr(user_host)));
}

static t_current_directory	get_dir_path(void)
{
	t_i8	dir_path[1024];

	dir_path[0] = '\0';
	getcwd(dir_path, sizeof(dir_path));
	if (dir_path[0] == '\0')
		return (dstr_c(cstr("unknown_directory")));
	else
		return (dstr_c(cstr(dir_path)));
}

static t_prompt_label	format_label(
	t_user_name user_name,
	t_host_name host_name,
	t_current_directory current_dir)
{
	t_prompt_label	res;

	res = user_name;
	str_insertc(&res, cstr("@"), res.len);
	if (res.s == NULL)
		return (res);
	str_insert(&res, &host_name, res.len);
	if (res.s == NULL)
		return (res);
	str_insertc(&res, cstr(":"), res.len);
	if (res.s == NULL)
		return (res);
	str_insert(&res, &current_dir, res.len);
	if (res.s == NULL)
		return (res);
	str_insertc(&res, cstr("$ "), res.len);
	if (res.s == NULL)
		return (res);
	return (res);
}

t_prompt_label	prompt_label(void)
{
	t_prompt_label		res;
	t_user_name			user_name;
	t_host_name			host_name;
	t_current_directory	current_dir;

	user_name = get_user_name();
	if (user_name.s == NULL)
		return (user_name);
	host_name = get_user_host();
	if (host_name.s == NULL)
		return (free_dstr(&user_name), host_name);
	current_dir = get_dir_path();
	if (current_dir.s == NULL)
		return (free_dstr(&user_name), free_dstr(&host_name), current_dir);
	res = format_label(user_name, host_name, current_dir);
	return (res);
}
