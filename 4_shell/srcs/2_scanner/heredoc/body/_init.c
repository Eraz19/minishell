/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:11:18 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 16:11:19 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc_body.h"
#include "heredoc_body_priv.h"

void	body_init(t_body *body)
{
	*(body) = (t_body){0};
	string_init(&body->content, 0, NULL, 0);
}

void	body_free(t_body *body)
{
	body->i = 0;
	string_free(&body->line);
	string_free(&body->input);
	string_free(&body->delim);
	string_free(&body->content);
	body->mode = HEREDOC_MODE_NORMAL;
}

t_error	body_load(t_body *body, t_lexer *lexer, t_token *delim, bool strip)
{
	if (lexer->input == NULL)
	{
		body->i = 0;
		if (!string_init(&body->input, 1, "", -1))
			return (body->err = error_sys());
	}
	else
	{
		body->i = lexer->input->i;
		if (!string_dup(&body->input, &lexer->input->str))
			return (body->err = error_sys());
	}
	if (strip)
		body->mode = HEREDOC_MODE_TAB_STRIP;
	else
		body->mode = HEREDOC_MODE_NORMAL;
	return (body->err = build_heredoc_delimiter(&body->delim, delim));
}
