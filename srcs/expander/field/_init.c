/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 10:32:04 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/18 13:35:12 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_field_.h"

void	expander_fields_init(t_expander_fields *fields)
{
	vector_init(fields, sizeof(t_expander_word), 0);
}

void	expander_fields_free(t_expander_fields *fields)
{
	vector_free(fields, (void (*)(void *))expander_word_free);
}
