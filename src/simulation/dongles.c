/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamps-v <rcamps-v@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 10:54:54 by rcamps-v          #+#    #+#             */
/*   Updated: 2026/07/29 12:23:06 by rcamps-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../coders/main.h"

static struct timespec	get_timespec_after_time(unsigned long time)
{
	struct timespec	final_time;
	unsigned long	abstime;

	abstime = current_ms() + time;
	final_time.tv_sec = abstime / 1000;
	final_time.tv_nsec = (abstime % 1000) * 1000000;
	return (final_time);
}

int	acquire_dongle(t_dongle *dongle, t_coder *coder)
{
	struct timespec	deadline;

	pthread_mutex_lock(&dongle->lock);
	while (
		(!dongle->available
			|| current_ms()
			< dongle->last_release_ms + coder->data->dongle_cooldown)
		&& coder->data->running)
	{
		deadline = get_timespec_after_time(10);
		pthread_cond_timedwait(
			&dongle->cond, &dongle->lock, &deadline);
	}
	if (!coder->data->running)
	{
		pthread_mutex_unlock(&dongle->lock);
		return (1);
	}
	dongle->available = false;
	pthread_mutex_unlock(&dongle->lock);
	log_status(coder->data, coder->id, TAKEN_DONGLE);
	return (0);
}
