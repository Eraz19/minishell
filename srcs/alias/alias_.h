/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 18:41:16 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/11 19:12:06 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALIAS__H
# define ALIAS__H

# include "alias.h"

void	alias_print_one(t_key_value *pair);
void	alias_print_all(t_key_value **pairs);
bool	is_token_aligeable_to_alias_expansion(t_alias *state, char *word);

#endif
