/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamps-v <rcamps-v@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 12:39:01 by rcamps-v          #+#    #+#             */
/*   Updated: 2026/08/26 12:08:42 by rcamps-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

int	init_dongle(t_dongle *dongle, unsigned int i, t_data *data)
{
	(void)data;
	dongle->id = i;
	dongle->available = true;
	dongle->last_release_ms = 0;
	dongle->wait_queue.head = NULL;
	dongle->wait_queue.size = 0;
	if (data->scheduler == FIFO)
	{
		dongle->wait_queue.cmp = cmp_fifo;
	}
	else
	{
		dongle->wait_queue.cmp = cmp_edf;
	}
	dongle->ready = false;
	if (pthread_mutex_init(&dongle->lock, NULL) != 0)
		return (1);
	if (pthread_cond_init(&dongle->cond, NULL) != 0)
	{
		pthread_mutex_destroy(&dongle->lock);
		return (1);
	}
	dongle->ready = true;
	return (0);
}

void	init_coder(t_coder *coder, unsigned int i, t_data *data)
{
	coder->id = i;
	coder->compiles_done = 0;
	coder->data = data;
	coder->last_compile_ms = data->start_time;
}

void	assign_dongles(t_coder *coder, unsigned int i, t_data *data)
{
	unsigned int	n;
	unsigned int	left_index;

	n = data->number_of_coders;
	left_index = (i + n - 1) % n;
	coder->left_idx = left_index;
	coder->right_idx = i;
	coder->left = &data->dongles[left_index];
	coder->right = &data->dongles[i];
}
