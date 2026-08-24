/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamps-v <rcamps-v@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 13:12:10 by rcamps-v          #+#    #+#             */
/*   Updated: 2026/08/22 13:12:57 by rcamps-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

int	cmp_fifo(t_request a, t_request b)
{
	if (a.arrival_order < b.arrival_order)
		return (-1);
	if (a.arrival_order > b.arrival_order)
		return (1);
	return (0);
}

int	cmp_edf(t_request a, t_request b)
{
	if (a.deadline < b.deadline)
		return (-1);
	if (a.deadline > b.deadline)
		return (1);
	return (cmp_fifo(a, b));
}

void	queue_push(t_queue *queue, t_request req)
{
	t_node	*new_node;
	t_node	**cursor;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return ;
	new_node->req = req;
	new_node->next = NULL;
	cursor = &queue->head;
	while (*cursor && queue->cmp((*cursor)->req, req) <= 0)
		cursor = &(*cursor)->next;
	new_node->next = *cursor;
	*cursor = new_node;
	queue->size++;
}

t_request	queue_pop(t_queue *queue)
{
	t_node		*old_head;
	t_request	req;

	if (!queue->head)
	{
		memset(&req, 0, sizeof(t_request));
		return (req);
	}
	old_head = queue->head;
	req = old_head->req;
	queue->head = old_head->next;
	free(old_head);
	queue->size--;
	return (req);
}
