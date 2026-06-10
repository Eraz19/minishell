/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __scanner.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 10:17:37 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 16:54:38 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SCANNER_H
# define __SCANNER_H

# include "types.h"
# include "scanner.h"
# include "lexer_.h"
# include "heredoc_.h"

t_error		reader_input(t_scanner_mode mode, char **input, char *path);

t_error		lexer_next_token(t_lexer *state, t_token *token);

t_error		heredoc_consume(t_heredoc *state, t_lexer *lexer);
t_error		heredoc_create_tmp_file(t_heredoc *state, t_file_path *file_path);

#endif
