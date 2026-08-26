/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamps-v <rcamps-v@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 11:58:03 by rcamps-v          #+#    #+#             */
/*   Updated: 2026/08/18 11:44:15 by rcamps-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

static void	alloc_arrays(t_data *data)
{
	data->coders = malloc(data->number_of_coders * sizeof(t_coder));
	if (!data->coders)
	{
		cleanup(data, "Error! Memory cannot be allocated.");
		exit(1);
	}
	data->dongles = malloc(data->number_of_coders * sizeof(t_dongle));
	if (!data->dongles)
	{
		cleanup(data, "Error! Memory cannot be allocated.");
		exit(1);
	}
	data->threads = malloc(data->number_of_coders * sizeof(pthread_t));
	if (!data->threads)
	{
		cleanup(data, "Error! Memory cannot be allocated.");
		exit(1);
	}
	memset(data->threads, 0, data->number_of_coders * sizeof(pthread_t));
	memset(data->coders, 0, data->number_of_coders * sizeof(t_coder));
	memset(data->dongles, 0, data->number_of_coders * sizeof(t_dongle));
}

static void	init_dongles_loop(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->number_of_coders)
	{
		if (init_dongle(&data->dongles[i], i, data) != 0)
		{
			cleanup(data, "Error! Could not initialize synchronization.");
			exit(1);
		}
		i++;
	}
}

static void	init_coders_loop(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->number_of_coders)
	{
		init_coder(&data->coders[i], i, data);
		assign_dongles(&data->coders[i], i, data);
		i++;
	}
}

static void	init_locks(t_data *data)
{
	data->log_lock_ready = false;
	data->sim_lock_ready = false;
	if (pthread_mutex_init(&data->log_lock, NULL) != 0)
	{
		cleanup(data, "Error! Could not initialize log mutex.");
		exit(1);
	}
	data->log_lock_ready = true;
	if (pthread_mutex_init(&data->sim_lock, NULL) != 0)
	{
		cleanup(data, "Error! Could not initialize sim mutex.");
		exit(1);
	}
	data->sim_lock_ready = true;
}

void	init_data(t_data *data)
{
	alloc_arrays(data);
	init_locks(data);
	init_dongles_loop(data);
	init_coders_loop(data);
}
