/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamps-v <rcamps-v@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 10:54:54 by rcamps-v          #+#    #+#             */
/*   Updated: 2026/08/26 12:08:23 by rcamps-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

static struct timespec	get_timespec_after_time(unsigned long time)
{
	struct timespec	final_time;
	unsigned long	abstime;

	abstime = current_ms() + time;
	final_time.tv_sec = abstime / 1000;
	final_time.tv_nsec = (abstime % 1000) * 1000000;
	return (final_time);
}

static void	enqueue_request(t_dongle *dongle, t_coder *coder)
{
	t_request	req;

	req.coder_id = coder->id;
	req.deadline = get_last_compile(coder) + coder->data->time_to_burnout;
	pthread_mutex_lock(&coder->data->log_lock);
	req.arrival_order = coder->data->request_counter++;
	pthread_mutex_unlock(&coder->data->log_lock);
	pthread_mutex_lock(&dongle->lock);
	queue_push(&dongle->wait_queue, req);
}

static int	can_acquire(t_dongle *dongle, t_coder *coder)
{
	if (!dongle->available)
		return (0);
	if (current_ms() < dongle->last_release_ms + coder->data->dongle_cooldown)
		return (0);
	if (!dongle->wait_queue.head)
		return (0);
	if (dongle->wait_queue.head->req.coder_id != coder->id)
		return (0);
	return (1);
}

int	acquire_dongle(t_dongle *dongle, t_coder *coder)
{
	struct timespec	deadline;

	enqueue_request(dongle, coder);
	while (get_running(coder->data))
	{
		if (can_acquire(dongle, coder))
			break ;
		deadline = get_timespec_after_time(10);
		pthread_cond_timedwait(&dongle->cond, &dongle->lock, &deadline);
	}
	if (!get_running(coder->data))
	{
		pthread_mutex_unlock(&dongle->lock);
		return (1);
	}
	dongle->available = false;
	queue_pop(&dongle->wait_queue);
	pthread_mutex_unlock(&dongle->lock);
	log_status(coder->data, coder->id, TAKEN_DONGLE);
	return (0);
}
