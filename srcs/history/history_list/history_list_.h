/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_list_.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 15:19:15 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 17:16:02 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_LIST__H
# define HISTORY_LIST__H

# include "error.h"
# include "libft.h"

typedef t_vector	t_history_list;

void	history_list_clean(void *item);
void	history_list_init(t_history_list *list);
void	history_list_free(t_history_list *list);

t_error	history_list_push(t_history_list *list, char *item);
t_error	history_list_get(char **item, size_t i, t_history_list *list);
t_error	history_list_insert(t_history_list *list, size_t index, char *item);
t_error	history_list_to_file(t_history_list *list, size_t i, t_buff *content);

#endif
