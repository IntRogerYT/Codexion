/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamps-v <rcamps-v@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 13:49:06 by rcamps-v          #+#    #+#             */
/*   Updated: 2026/07/20 11:36:11 by rcamps-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../coders/main.h"

char	**remove_first_arg(char **argv)
{
	char	**args;
	int		i;

	args = (char **)malloc(9 * sizeof(char *) + 1);
	if (args == NULL)
		return (NULL);
	i = 0;
	while (i <= 7)
	{
		args[i] = argv[i + 1];
		i++;
	}
	args[i] = NULL;
	return (args);
}

void	convert_arg_types(char **args, t_data *data)
{
	data->number_of_coders = atoi(args[0]);
	data->time_to_burnout = atoi(args[1]);
	data->time_to_compile = atoi(args[2]);
	data->time_to_debug = atoi(args[3]);
	data->time_to_refactor = atoi(args[4]);
	data->number_of_compiles_required = atoi(args[5]);
	data->dongle_cooldown = atoi(args[6]);
	if (!strcmp(args[7], "edf"))
		data->scheduler = EDF;
	else if (!strcmp(args[7], "fifo"))
		data->scheduler = FIFO;
	else
		free_error(args, data, "The scheduler must be 'edf' or 'fifo'.");
}

void	parse_args(int argc, char **argv, t_data *data)
{
	char	**args;
	int		i;

	if (argc != 9)
	{
		printf("Error! 8 parameters are needed. The program runs like this:\n");
		printf("$> ./codexion <number_of_coders> <time_to_burnout> ");
		printf("<time_to_compile> <time_to_debug> <time_to_refactor> ");
		printf("<number_of_compiles_required> <dongle_cooldown> <scheduler>");
		exit(1);
	}
	args = remove_first_arg(argv);
	i = 0;
	while (i < 7)
	{
		if (!ft_isnumber(args[i++]))
		{
			printf("All first 7 arguments must be positive integers.");
			exit(1);
		}
	}
	if (!ft_strisalpha(args[7]))
		free_error(args, data, "The last argument must be 'edf' or 'fifo'.");
	convert_arg_types(args, data);
	free(args);
}
