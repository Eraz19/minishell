/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 16:05:23 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/11 17:07:28 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER_H
# define SCANNER_H

# include "error.h"
# include "libft.h"
# include "types.h"
# include "../srcs/scanner/lexer/_lexer.h"

typedef enum e_scanner_mode
{
	TTY,
	SCRIPT,
	STRING,
}	t_scanner_mode;

typedef struct s_scanner
{
	t_scanner_mode	mode;
	t_lexer			*lexer;
}	t_scanner;

void	scanner_init(t_scanner *scanner);
void	scanner_free(t_scanner **scanner);
t_error scanner_load(t_scanner_mode mode, const char *source);

t_token	*scanner_get_next_token(t_scanner *scanner);

#endif
