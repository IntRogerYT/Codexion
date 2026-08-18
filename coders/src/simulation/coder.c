/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamps-v <rcamps-v@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 11:52:35 by rcamps-v          #+#    #+#             */
/*   Updated: 2026/08/18 09:39:03 by rcamps-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

static void	sleep_ms(unsigned long time, t_coder *coder)
{
	unsigned long	loop_times;

	loop_times = (time + 9) / 10;
	while (loop_times-- && coder->data->running)
		usleep(10000);
}

void	*routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	while (coder->compiles_done < coder->data->number_of_compiles_required
		&& coder->data->running)
	{
		if (acquire_both_dongles(coder) != 0)
			return (NULL);
		log_status(coder->data, coder->id, COMPILING);
		coder->last_compile_ms = current_ms();
		sleep_ms(coder->data->time_to_compile, coder);
		coder->compiles_done++;
		release_both_dongles(coder);
		log_status(coder->data, coder->id, DEBUGGING);
		sleep_ms(coder->data->time_to_debug, coder);
		log_status(coder->data, coder->id, REFACTORING);
		sleep_ms(coder->data->time_to_refactor, coder);
	}
	return (NULL);
}
