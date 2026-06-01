/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   API.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 16:05:54 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/01 09:46:27 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_scanner.h"
#include "./lexer/context/_context.h"

t_error	scanner_next_token(t_token *res)
{
	t_error		err;
	t_scanner	scanner;

	if (res == NULL)
		return (ERR_NULL_ARGS);
	err = ERR_NO;
	scanner = shell_get_scanner();
	if (scanner.mode == SCAN_MODE_FILE)
		err = reader_file_input(&scanner.lexer.input, scanner.origin.path);
	else if (scanner.mode == SCAN_MODE_STRING)
		scanner.lexer.input = scanner.origin.command;
	else if (scanner.lexer.input == NULL)
		err = reader_new_input(&scanner.lexer.input);
	if (err != ERR_NO)
		return (err);
	return (lexer_next_token(res, &scanner.lexer));
}

t_error	scanner_report_io_here(char **res, t_buff delim, t_heredoc_mode mode)
{
	t_error				err;
	t_here_queue_item	item;
	t_scanner			scanner;

	scanner = shell_get_scanner();
	err = lexer_heredoc_create_tmp_file(res);
	if (err != ERR_NO)
		return (err);
	item = (t_here_queue_item){
		.path = *res,
		.mode = mode,
		.delim = delim};
	return (here_queue_push(scanner.lexer.queue, item));
}

bool	scanner_is_in_quoting_whitelist(char c, t_scanner_ctx ctx)
{
	if (ctx == NONE_)
		return (is_in_ctx_none_whitelist(c));
	else if (ctx == SQUOTE)
		return (is_in_ctx_squote_whitelist(c));
	else if (ctx == DQUOTE)
		return (is_in_ctx_dquote_whitelist(c));
	else if (ctx == DOLLAR_SQUOTE)
		return (is_in_ctx_dollar_squote_whitelist(c));
	else
		return (false);
}

bool	scanner_is_quoting_ending(char c, t_scanner_ctx ctx)
{
	if (ctx == SQUOTE)
		return (is_ctx_squote_ending(c));
	else if (ctx == DQUOTE)
		return (is_ctx_dquote_ending(c));
	else if (ctx == DOLLAR_SQUOTE)
		return (is_ctx_dollar_squote_ending(c));
	else
		return (false);
}
