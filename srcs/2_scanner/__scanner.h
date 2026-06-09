/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __scanner.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 10:17:37 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/08 15:03:10 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SCANNER_H
# define __SCANNER_H

# include "types.h"
# include "__alias.h"
# include "__lexer.h"
# include "__heredoc.h"

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
	
t_scanner	*shell_get_scanner(void);

t_error		reader_input(t_scanner_mode mode, char **input, char *path);

t_error		lexer_next_token(t_lexer *state, t_token *token);

t_error		heredoc_consume(t_heredoc *state, t_lexer *lexer);
t_error		heredoc_create_tmp_file(t_heredoc *state, t_file_path *file_path);

#endif
