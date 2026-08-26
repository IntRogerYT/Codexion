/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamps-v <rcamps-v@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 12:54:44 by rcamps-v          #+#    #+#             */
/*   Updated: 2026/08/24 09:57:31 by rcamps-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./main.h"

int	main(int argc, char **argv)
{
	t_data	*parsed_data;

	parsed_data = malloc(sizeof(t_data));
	if (!parsed_data)
		error("Error! Memory cannot be allocated. There is not enough space.");
	memset(parsed_data, 0, sizeof(t_data));
	parse_args(argc, argv, parsed_data);
	parsed_data->start_time = current_ms();
	init_data(parsed_data);
	run_simulation(parsed_data);
	cleanup(parsed_data, NULL);
	return (0);
}
