/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamps-v <rcamps-v@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 10:54:54 by rcamps-v          #+#    #+#             */
/*   Updated: 2026/08/13 10:28:50 by rcamps-v         ###   ########.fr       */
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

void	release_dongle(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->lock);
	dongle->available = true;
	dongle->last_release_ms = current_ms();
	pthread_mutex_unlock(&dongle->lock);
	pthread_cond_broadcast(&dongle->cond);
}

int	acquire_both_dongles(t_coder *coder)
{
	t_dongle		*first;
	t_dongle		*second;

	if (coder->left == coder->right)
		return (acquire_dongle(coder->left, coder));
	if (coder->left_idx < coder->right_idx)
	{
		first = coder->left;
		second = coder->right;
	}
	else
	{
		first = coder->right;
		second = coder->left;
	}
	if (acquire_dongle(first, coder) != 0)
		return (1);
	if (acquire_dongle(second, coder) != 0)
	{
		release_dongle(first);
		return (1);
	}
	return (0);
}

void	release_both_dongles(t_coder *coder)
{
	release_dongle(coder->left);
	if (coder->right != coder->left)
		release_dongle(coder->right);
}
