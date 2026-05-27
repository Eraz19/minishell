/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _backslash.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 16:21:05 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/19 09:41:23 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __BACKSLASH_H
# define __BACKSLASH_H

# include "../../_context.h"
# include "../../../_lexer.h"

void	consume_line_continuation(t_lexer *lexer);

#endif
