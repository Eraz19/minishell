/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   body_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:11:21 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 16:29:15 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc_body_priv.h"

t_error	error_missing_delimiter(t_body *body)
{
	body->delim.data[body->delim.len - 1] = '\0';
	body->err = error_print(
			error(ERR_NO_DELIM),
			"heredoc",
			NULL,
			"'%s'",
			body->delim.data);
	return (body->err);
}
