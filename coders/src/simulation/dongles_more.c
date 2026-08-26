/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles_more.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamps-v <rcamps-v@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 12:57:00 by rcamps-v          #+#    #+#             */
/*   Updated: 2026/08/26 12:57:00 by rcamps-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

void	release_dongle(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->lock);
	dongle->available = true;
	dongle->last_release_ms = current_ms();
	pthread_cond_broadcast(&dongle->cond);
	pthread_mutex_unlock(&dongle->lock);
}

int	acquire_both_dongles(t_coder *coder)
{
	t_dongle	*first;
	t_dongle	*second;

	if (coder->left == coder->right)
		return (acquire_dongle(coder->left, coder));
	first = coder->left;
	second = coder->right;
	if (coder->left_idx > coder->right_idx)
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
