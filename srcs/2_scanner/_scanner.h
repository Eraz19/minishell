/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _scanner.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 10:17:37 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/01 11:28:53 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _SCANNER_H
# define _SCANNER_H

# include "./lexer/_lexer.h"
# include "./reader/_reader.h"

typedef enum e_scanner_mode
{
	SCAN_NONE,
	SCAN_MODE_FILE,
	SCAN_MODE_STDIN,
	SCAN_MODE_STRING
}	t_scanner_mode;

typedef char*	t_scanner_path;
typedef char*	t_scanner_command;

typedef union u_scanner_origin
{
	t_scanner_path		path;
	t_scanner_command	command;
}	t_scanner_origin;

typedef struct s_scanner
{
	t_scanner_mode		mode;
	t_lexer				lexer;
	t_scanner_origin	origin;
	t_reader			reader;
}	t_scanner;

t_scanner	shell_get_scanner(void);

t_error		reader_heredoc(char **res);
t_error		reader_new_input(char **res);
t_error		reader_continuation(char **res);
t_error		reader_file_input(char **res, t_scanner_path path);

t_error		lexer_next_token(t_token *res, t_lexer *state);

#endif
