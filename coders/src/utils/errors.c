/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamps-v <rcamps-v@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 13:24:08 by rcamps-v          #+#    #+#             */
/*   Updated: 2026/08/18 09:39:03 by rcamps-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

void	error(char *message)
{
	printf("%s", message);
	exit(1);
}

void	free_error(char **args, t_data *data, char *message)
{
	if (args)
		free(args);
	cleanup(data, message);
	exit(1);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}

static void	destroy_dongles(t_data *data)
{
	unsigned int	i;

	if (!data->dongles)
		return ;
	i = 0;
	while (i < data->number_of_coders)
	{
		if (data->dongles[i].ready)
		{
			pthread_mutex_destroy(&data->dongles[i].lock);
			pthread_cond_destroy(&data->dongles[i].cond);
		}
		i++;
	}
	free(data->dongles);
}

void	cleanup(t_data *data, char *message)
{
	if (data)
	{
		destroy_dongles(data);
		if (data->log_lock_ready)
			pthread_mutex_destroy(&data->log_lock);
		if (data->coders)
			free(data->coders);
		free(data);
	}
	if (message)
		printf("%s\n", message);
}
