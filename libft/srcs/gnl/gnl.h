/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:01:29 by adouieb           #+#    #+#             */
/*   Updated: 2026/02/02 17:55:20 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# include "libft_gnl.h"

void			read_file(t_reader *reader_content, t_u32 fd);
t_reader_node	*select_reader_node(t_readers *readers, t_u32 fd);

#endif