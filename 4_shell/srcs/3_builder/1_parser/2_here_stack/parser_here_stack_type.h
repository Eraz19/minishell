/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_here_stack_type.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:06:54 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:06:56 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HERE_STACK_TYPE_H
# define PARSER_HERE_STACK_TYPE_H

# include "libft.h"

/**
 * @ingroup parser_here_stack
 * @typedef t_parser_here_stack
 * @brief Pending here-document nodes, in reduction order, backed by a
 *        @ref t_vector of @c t_cst_node pointers (borrowed: the nodes
 *        belong to the syntax tree).
 */
typedef t_vector	t_parser_here_stack;

#endif
