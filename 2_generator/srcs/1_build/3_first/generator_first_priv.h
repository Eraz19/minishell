/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator_first_priv.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:43:13 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/04 16:43:14 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERATOR_FIRST_PRIV_H
# define GENERATOR_FIRST_PRIV_H

# include <stdbool.h>

void	first_add(bool *dst, bool *did_add);
void	first_add_list(bool *dst, const bool *src, bool *did_add);

#endif
