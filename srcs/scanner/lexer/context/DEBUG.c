/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DEBUG.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 13:21:46 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/13 15:39:20 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "_context.h"

char	*DEBUG_ctx_type_stringify(t_lexer_ctx_type type)
{
	if (type == NONE    ) return (str_join("", "NONE"    ));
	if (type == SQUOTE  ) return (str_join("", "SQUOTE"	 ));
	if (type == DQUOTE  ) return (str_join("", "DQUOTE"	 ));
	if (type == BACKTICK) return (str_join("", "BACKTICK"));
	if (type == CMD_SUB ) return (str_join("", "CMD_SUB" ));
	if (type == ARITH   ) return (str_join("", "ARITH"	 ));
	if (type == PARAM   ) return (str_join("", "PARAM"	 ));
	if (type == ESCAPED ) return (str_join("", "ESCAPED" ));
	return (NULL);
}
