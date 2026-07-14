/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamps-v <rcamps-v@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 13:49:06 by rcamps-v          #+#    #+#             */
/*   Updated: 2026/07/14 14:18:26 by rcamps-v         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../coders/main.h"

char	**remove_first_arg(char **argv)
{
	char	**args;
	int		i;

	args = (char **)malloc(8 * sizeof(char *) + 1);
	if (args == NULL)
		return (NULL);
	i = 0;
	while (i <= 7)
	{
		args[i] = (char *)malloc(strlen(argv[i]) * sizeof(char) + 1);
		if (!args[i])
			return (NULL);
		i++;
	}
	i = 0;
	while (i <= 7)
	{
		args[i] = argv[i + 1];
		i++;
	}
	args[i] = NULL;
	return (args);
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
	while (i < 8)
	{
		if (!ft_isnumber(args[i]))
		{
			printf("All first 7 arguments must be positive integers.");
			exit(1);
		}
	}
	printf("%i\n", data->number_of_coders);
}
