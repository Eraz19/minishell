/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_priv.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:11:43 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 15:08:18 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_PRIV_H
# define FUNCTIONS_PRIV_H

# include "functions.h"

// Life cycle

void	function_free(t_function **function);
void	function_init(t_function *function);
void	function_free(t_function **function);

#endif
