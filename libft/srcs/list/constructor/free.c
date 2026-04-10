/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 16:57:38 by adouieb           #+#    #+#             */
/*   Updated: 2026/02/02 15:41:46 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list.h"

/**
 * free_node - Deletes and frees a node of a list
 *
 * @param lst The list from which to delete the node
 * @param node The node pointer to delete
 * @param del Function to delete the content of the node
 *
 * @args: If lst or del is NULL, does nothing.
 *        If index is out of bounds, does nothing.
 */
void	free_node(t_lst *lst, t_node *node, void (*del)(void*))
{
	size_t	i;
	t_node	*prev;
	t_node	*current;

	if (lst == NULL || del == NULL || node == NULL)
		return ;
	1 && (i = 0, prev = NULL, current = lst->nodes);
	while (current != node && i < lst->size)
		1 && (prev = current, current = current->next, i++);
	del(current->content);
	if (prev != NULL)
		prev->next = current->next;
	else
		lst->nodes = current->next;
	free(current);
	lst->size--;
}

/**
 * free_lst - Deletes and frees all nodes of a list
 *
 * @param lst The list from which to delete the nodes
 * @param del Function to delete the content of a node
 *
 * @args: If lst, lst.nodes or del is NULL, does nothing.
 */
void	free_lst(t_lst *lst, void (*del)(void*))
{
	t_node	*next;
	t_node	*current;

	if (lst == NULL || lst->nodes == NULL || del == NULL)
		return ;
	1 && (next = NULL, current = lst->nodes);
	while (lst->size > 0)
	{
		next = current->next;
		del(current->content);
		current->content = NULL;
		current->next = NULL;
		free(current);
		1 && (lst->size--, current = next);
	}
	lst->nodes = NULL;
	lst->size = 0;
}
