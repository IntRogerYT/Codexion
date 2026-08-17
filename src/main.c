/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamps-v <rcamps-v@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 12:54:44 by rcamps-v          #+#    #+#             */
/*   Updated: 2026/08/13 12:41:22 by rcamps-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/main.h"

int	main(int argc, char **argv)
{
	t_data	*parsed_data;
	parsed_data = malloc(sizeof(t_data));
	if (!parsed_data)
		error("Error! Memory cannot be allocated. There is not enough space.");
	memset(parsed_data, 0, sizeof(t_data));
	parse_args(argc, argv, parsed_data);
	printf("./codexion %i %i %i %i %i %i %i %i\n",
		parsed_data->number_of_coders,
		parsed_data->time_to_burnout,
		parsed_data->time_to_compile,
		parsed_data->time_to_debug,
		parsed_data->time_to_refactor,
		parsed_data->number_of_compiles_required,
		parsed_data->dongle_cooldown,
		parsed_data->scheduler);
	parsed_data->start_time = current_ms();
	init_data(parsed_data);
	printf("data initialized correctly!\n");
	cleanup(parsed_data, NULL);
	printf("all correctly\n");
	return (0);
}
