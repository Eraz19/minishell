/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _escape.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 16:21:05 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/11 16:30:49 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _ESCAPE_H
# define _ESCAPE_H

# include <stddef.h>

bool	escape_char_in_backtick(size_t *i);
bool	escape_char_in_param(char *input_ptr, size_t *i);
bool	escape_char_in_arithm(char *input_ptr, size_t *i);
bool	escape_char_in_dquote(char *input_ptr, size_t *i);
bool	escape_char_in_no_ctx(char *input_ptr, size_t *i);

#endif
