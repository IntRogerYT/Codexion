/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamps-v <rcamps-v@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 12:12:44 by rcamps-v          #+#    #+#             */
/*   Updated: 2026/08/22 13:13:24 by rcamps-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

void	run_simulation(t_data *data)
{
	int	i;

	i = 0;
	data->running = true;
	while ((unsigned int)i < data->number_of_coders)
	{
		if (pthread_create(&data->threads[i], NULL, routine, &data->coders[i]))
		{
			while (--i >= 0)
				pthread_join(data->threads[i], NULL);
			cleanup(data, "Error! A thread cannot be created. Aborting...");
			exit(1);
		}
		i++;
	}
	pthread_create(&data->monitor, NULL, monitor_routine, data);
	i = 0;
	while ((unsigned int)i < data->number_of_coders)
	{
		pthread_join(data->threads[i], NULL);
		i++;
	}
	pthread_join(data->monitor, NULL);
}

void	*monitor_routine(void *arg)
{
	t_data			*data;
	unsigned int	finished_coders;

	data = (t_data *)arg;
	while (data->running)
	{
		finished_coders = 0;
		coders_loop(data, &finished_coders);
		usleep(1000);
		if (finished_coders == data->number_of_coders)
			data->running = false;
	}
	return (NULL);
}

void	coders_loop(t_data *data, unsigned int *finished_coders)
{
	unsigned int	i;

	i = 0;
	while (i < data->number_of_coders)
	{
		if (current_ms() - data->coders[i].last_compile_ms
			>= data->time_to_burnout)
		{
			log_status(data, i, BURNED_OUT);
			data->running = false;
			break ;
		}
		if (data->coders[i].compiles_done >= data->number_of_compiles_required)
			(*finished_coders)++;
		i++;
	}
}
