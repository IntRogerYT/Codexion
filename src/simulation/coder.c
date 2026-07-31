/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamps-v <rcamps-v@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 11:52:35 by rcamps-v          #+#    #+#             */
/*   Updated: 2026/07/29 10:44:00 by rcamps-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../coders/main.h"

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
	while (coder->compiles_done < coder->data->number_of_compiles_required)
	{
		log_status(coder->data, coder->id, TAKEN_DONGLE);
		log_status(coder->data, coder->id, TAKEN_DONGLE);
		log_status(coder->data, coder->id, COMPILING);
		sleep_ms(coder->data->time_to_compile, coder);
		coder->compiles_done++;
		coder->last_compile_ms = current_ms();
		log_status(coder->data, coder->id, DEBUGGING);
		sleep_ms(coder->data->time_to_debug, coder);
		log_status(coder->data, coder->id, REFACTORING);
		sleep_ms(coder->data->time_to_refactor, coder);
	}
	return (NULL);
}
