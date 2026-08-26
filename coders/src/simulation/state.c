/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamps-v <rcamps-v@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 13:02:00 by rcamps-v          #+#    #+#             */
/*   Updated: 2026/08/26 13:02:00 by rcamps-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

bool	get_running(t_data *data)
{
	bool	ret;

	pthread_mutex_lock(&data->sim_lock);
	ret = data->running;
	pthread_mutex_unlock(&data->sim_lock);
	return (ret);
}

void	set_running(t_data *data, bool value)
{
	pthread_mutex_lock(&data->sim_lock);
	data->running = value;
	pthread_mutex_unlock(&data->sim_lock);
}

unsigned long	get_last_compile(t_coder *coder)
{
	unsigned long	ret;

	pthread_mutex_lock(&coder->data->sim_lock);
	ret = coder->last_compile_ms;
	pthread_mutex_unlock(&coder->data->sim_lock);
	return (ret);
}

void	set_last_compile(t_coder *coder, unsigned long value)
{
	pthread_mutex_lock(&coder->data->sim_lock);
	coder->last_compile_ms = value;
	pthread_mutex_unlock(&coder->data->sim_lock);
}

unsigned int	get_compiles_done(t_coder *coder)
{
	unsigned int	ret;

	pthread_mutex_lock(&coder->data->sim_lock);
	ret = coder->compiles_done;
	pthread_mutex_unlock(&coder->data->sim_lock);
	return (ret);
}
