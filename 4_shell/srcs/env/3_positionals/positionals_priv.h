/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positionals_priv.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:10:30 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:10:31 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POSITIONALS_PRIV_H
# define POSITIONALS_PRIV_H

/**
 * @brief Free a positional frame for vector_free() callbacks.
 *
 * The @c void* signature matches @ref vector_free().
 *
 * @param positionals Positional frame to release (borrowed).
 */
void	positionals_free_item(void *positionals);

#endif
