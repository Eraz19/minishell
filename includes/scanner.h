/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 16:05:23 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/09 17:35:29 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER_H
# define SCANNER_H

# include "__lexer.h"
# include "__alias.h"
# include "__heredoc.h"
# include "context.h"
# include "error.h"
# include "types.h"

typedef enum e_scanner_mode
{
	SCAN_NONE,
	SCAN_MODE_FILE,
	SCAN_MODE_STDIN,
	SCAN_MODE_STRING
}	t_scanner_mode;

typedef char*	t_scanner_command;

typedef union u_scanner_arg
{
	t_file_path			path;
	t_scanner_command	command;
}	t_scanner_arg;

typedef struct s_scanner
{
	t_error			err;
	t_scanner_arg	arg;
	t_scanner_mode	mode;
	t_alias			alias;
	t_lexer			lexer;
	t_heredoc		heredoc;
}	t_scanner;

void	scanner_init(t_scanner *state);
void	scanner_free(t_scanner *state);
t_error	scanner_load(t_scanner *state, t_scanner_mode mode, const char *arg);

// @warning: res must have been init/cleaned with token_init() before call this function
t_error	scanner_next_token(t_token *res);
bool	scanner_is_quoting_ending(char c, t_context context);
bool	scanner_is_in_quoting_whitelist(char c, t_context context);
t_error	scanner_report_io_here(char **res, t_buff delim, t_heredoc_mode mode);

#endif
