/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 16:05:23 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/11 16:52:56 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER_H
# define SCANNER_H

# include "error.h"
# include "types.h"
# include "lexer_.h"
# include "heredoc_.h"
# include "context.h"

typedef enum e_scanner_mode
{
	SCAN_NONE,
	SCAN_FILE,
	SCAN_STDIN,
	SCAN_STRING
}	t_scanner_mode;

typedef struct s_scanner
{
	t_error			err;
	t_scanner_mode	mode;
	t_lexer			lexer;
	const char		*source;
	t_heredoc		heredoc;
}	t_scanner;

void	scanner_init(t_scanner *state);
void	scanner_free(t_scanner *state);
t_error	scanner_load(t_scanner *state, t_scanner_mode mode, const char *source);

// @warning: res must have been init/cleaned with token_init() before call this function
t_error	scanner_next_token(t_token *res);
bool	scanner_is_quoting_ending(char c, t_context context);
bool	scanner_is_in_quoting_whitelist(char c, t_context context);
t_error	scanner_report_io_here(char **res, t_buff delim, t_heredoc_mode mode);

#endif
