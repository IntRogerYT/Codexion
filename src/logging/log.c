/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamps-v <rcamps-v@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 10:24:56 by rcamps-v          #+#    #+#             */
/*   Updated: 2026/07/27 10:46:03 by rcamps-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../coders/main.h"

static const char	*state_to_label(t_state state)
{
	if (state == TAKEN_DONGLE)
		return ("has taken a dongle");
	if (state == COMPILING)
		return ("is compiling");
	if (state == DEBUGGING)
		return ("is debugging");
	if (state == REFACTORING)
		return ("is refactoring");
	return ("burned out");
}

unsigned long	current_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((unsigned long)(tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

unsigned long	get_elapsed_ms(t_data *data)
{
	return (current_ms() - data->start_time);
}

void	log_status(t_data *data, unsigned int coder_id, t_state state)
{
	unsigned long	elapsed;

	elapsed = get_elapsed_ms(data);
	pthread_mutex_lock(&data->log_lock);
	printf("%lu %u %s\n", elapsed, coder_id, state_to_label(state));
	pthread_mutex_unlock(&data->log_lock);
}
