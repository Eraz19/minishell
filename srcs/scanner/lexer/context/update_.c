/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:08:42 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/11 13:56:48 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../_scanner.h"

int	update_ctx_in_backtick(t_ctx_stack *ctx, char *input_ptr, size_t *i)
{
	if (input_ptr[0] == '`')
		return ((*i)++, ctx_pop(ctx), 1);
	else if (input_ptr[0] == '\\' && input_ptr[1] == '`')
		return ((*i) += 2, ctx_push(ctx, BACKTICK));
	return (-1);
}

int	update_ctx_in_squote(t_ctx_stack *ctx, char *input_ptr, size_t *i)
{
	if (input_ptr[0] == '\'')
		return ((*i)++, ctx_pop(ctx), 1);
	return (-1);
}
