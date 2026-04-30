/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _scanner.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 17:16:40 by adouieb           #+#    #+#             */
/*   Updated: 2026/04/29 18:07:53 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _SCANNER_H
# define _SCANNER_H

#include "scanner.h"

char	*remove_escapable_newlines(char *input);

bool	is_contains_eof(t_lexer *lexer);

#endif
