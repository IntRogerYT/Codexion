/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamps-v <rcamps-v@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 14:06:23 by rcamps-v          #+#    #+#             */
/*   Updated: 2026/08/18 09:39:03 by rcamps-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

void	validate_args(char **args, t_data *data)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (!ft_isnumber(args[i]))
			free_error(args, data,
				"All first 7 arguments must be positive integers.");
		i++;
	}
	if (!ft_strisalpha(args[7]))
		free_error(args, data, "The last argument must be 'edf' or 'fifo'.");
	if (atoi(args[0]) < 1)
		free_error(args, data, "The number of coders must be more than 0");
}
