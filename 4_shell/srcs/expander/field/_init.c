/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:43:27 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:43:28 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "field_.h"

void	fields_init(t_fields *fields)
{
	vector_init(fields, sizeof(t_word), 0);
}

void	fields_free(t_fields *fields)
{
	vector_free(fields, (void (*)(void *))word_free);
}
