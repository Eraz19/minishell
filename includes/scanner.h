/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 16:05:23 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/29 18:24:56 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER_H
# define SCANNER_H

# include "../srcs/2_scanner/_scanner.h"
# include "../srcs/2_scanner/lexer/_lexer.h"

typedef t_token			t_lexer_token;
typedef t_token_type	t_lexer_token_type;

void	scanner_init(t_scanner *res);
void	scanner_free(t_scanner *res);
t_error	scanner_load(t_scanner *res, t_scanner_mode mode,
			t_scanner_origin origin);

t_error	scanner_next_token(t_token *res);
bool	scanner_is_quoting_ending(char c, t_scanner_ctx ctx);
bool	scanner_is_in_quoting_whitelist(char c, t_scanner_ctx ctx);
t_error	scanner_report_io_here(char **res, t_buff delim, t_heredoc_mode mode);

#endif
