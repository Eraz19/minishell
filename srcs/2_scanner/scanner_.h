/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 10:17:37 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/11 17:07:51 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER__H
# define SCANNER__H

# include "scanner.h"

t_error		scanner_read_input(t_scanner *state);
t_error		scanner_heredoc_store(t_scanner *state);
t_error		scanner_alias_expand(t_scanner *state, t_token *token);

bool		is_EOF(t_scanner *state);
t_error		lexer_next_token(t_lexer *state, t_token *token);
t_error		heredoc_consume(t_heredoc *state, t_lexer *lexer);
t_error		heredoc_create_tmp_file(t_heredoc *state, t_file_path *file_path);

#endif
