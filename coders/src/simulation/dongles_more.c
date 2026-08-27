/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles_more.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamps-v <rcamps-v@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 12:57:00 by rcamps-v          #+#    #+#             */
/*   Updated: 2026/08/27 11:10:24 by rcamps-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

static void	enqueue_both(t_dongle *first, t_dongle *second, t_coder *coder)
{
	t_request	req;

	req.coder_id = coder->id;
	req.deadline = get_last_compile(coder) + coder->data->time_to_burnout;
	pthread_mutex_lock(&coder->data->log_lock);
	req.arrival_order = coder->data->request_counter++;
	pthread_mutex_unlock(&coder->data->log_lock);
	pthread_mutex_lock(&first->lock);
	queue_push(&first->wait_queue, req);
	pthread_mutex_unlock(&first->lock);
	pthread_mutex_lock(&second->lock);
	queue_push(&second->wait_queue, req);
	pthread_mutex_unlock(&second->lock);
}

static int	acquire_success(t_dongle *f, t_dongle *s, t_coder *coder)
{
	f->available = false;
	s->available = false;
	queue_pop(&f->wait_queue);
	queue_pop(&s->wait_queue);
	pthread_mutex_unlock(&s->lock);
	pthread_mutex_unlock(&f->lock);
	log_status(coder->data, coder->id, TAKEN_DONGLE);
	return (0);
}

static int	attempt_lock_both(t_dongle *f, t_dongle *s, t_coder *coder)
{
	struct timespec	dl;

	pthread_mutex_lock(&f->lock);
	pthread_mutex_lock(&s->lock);
	if (can_acquire(f, coder) && can_acquire(s, coder))
		return (acquire_success(f, s, coder));
	dl = get_future_timespec(10);
	if (!can_acquire(f, coder))
	{
		pthread_mutex_unlock(&s->lock);
		pthread_cond_timedwait(&f->cond, &f->lock, &dl);
		pthread_mutex_unlock(&f->lock);
	}
	else
	{
		pthread_mutex_unlock(&f->lock);
		pthread_cond_timedwait(&s->cond, &s->lock, &dl);
		pthread_mutex_unlock(&s->lock);
	}
	return (1);
}

int	acquire_both_dongles(t_coder *coder)
{
	t_dongle	*f;
	t_dongle	*s;

	if (coder->left == coder->right)
	{
		if (acquire_dongle(coder->left, coder) != 0)
			return (1);
		while (get_running(coder->data))
			usleep(1000);
		release_dongle(coder->left);
		return (1);
	}
	f = coder->left;
	s = coder->right;
	if (coder->left_idx > coder->right_idx)
	{
		f = coder->right;
		s = coder->left;
	}
	enqueue_both(f, s, coder);
	while (get_running(coder->data))
		if (!attempt_lock_both(f, s, coder))
			return (0);
	return (1);
}

void	release_both_dongles(t_coder *coder)
{
	release_dongle(coder->left);
	if (coder->right != coder->left)
		release_dongle(coder->right);
}
