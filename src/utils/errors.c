/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamps-v <rcamps-v@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 13:24:08 by rcamps-v          #+#    #+#             */
/*   Updated: 2026/07/20 11:34:38 by rcamps-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../coders/main.h"

void	error(char *message)
{
	printf("%s", message);
	exit(1);
}

void	free_error(char **args, t_data *data, char *message)
{
	if (args)
	{
		free(args);
	}
	if (data)
		free(data);
	if (message)
		printf("%s\n", message);
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
