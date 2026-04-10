/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 13:33:15 by adouieb           #+#    #+#             */
/*   Updated: 2026/04/09 17:08:31 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include "prompt_display.h"

t_prompt_input	display_prompt(t_dstr label)
{
	t_prompt_input	res;
	t_i8			*user_input;

	if (label.s == NULL)
		return (label);
	user_input = readline(label.s);
	if (user_input == NULL)
		return (free_dstr(&label), dstr_s(0));
	res = dstr_c(cstr(user_input));
	if (res.s == NULL)
		return (free(user_input), free_dstr(&label), dstr_s(0));
	return (free(user_input), free_dstr(&label), user_input = NULL, res);
}
