/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _reader.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 10:37:09 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/01 09:55:58 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _READER_H
# define _READER_H

# include "error.h"
# include "../ctx_stack/_ctx_stack.h"

// Forwarded types
typedef char*	t_scanner_path;

typedef struct s_reader
{
	t_scanner_ctx_stack	*ctx;
}	t_reader;

void	reader_init(t_reader *state);
void	reader_free(t_reader *state);
void	reader_load(t_reader *state, t_scanner_ctx_stack *ctx);

#endif
