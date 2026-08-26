/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamps-v <rcamps-v@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 11:52:35 by rcamps-v          #+#    #+#             */
/*   Updated: 2026/08/26 11:52:04 by rcamps-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

static void	sleep_ms(unsigned long time, t_coder *coder)
{
	unsigned long	loop_times;

	loop_times = (time + 9) / 10;
	while (loop_times-- && get_running(coder->data))
	{
		usleep(10000);
	}
}

static int	compile_debug_refactor(t_coder *coder)
{
	if (acquire_both_dongles(coder) != 0)
		return (0);
	log_status(coder->data, coder->id, COMPILING);
	set_last_compile(coder, current_ms());
	sleep_ms(coder->data->time_to_compile, coder);
	inc_compiles_done(coder);
	release_both_dongles(coder);
	if (!get_running(coder->data))
		return (0);
	log_status(coder->data, coder->id, DEBUGGING);
	sleep_ms(coder->data->time_to_debug, coder);
	if (!get_running(coder->data))
		return (0);
	log_status(coder->data, coder->id, REFACTORING);
	sleep_ms(coder->data->time_to_refactor, coder);
	return (1);
}

void	*routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	while (get_compiles_done(coder) < coder->data->number_of_compiles_required
		&& get_running(coder->data))
	{
		if (!compile_debug_refactor(coder))
			break ;
	}
	return (NULL);
}
