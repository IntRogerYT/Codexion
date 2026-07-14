/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamps-v <rcamps-v@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 12:54:44 by rcamps-v          #+#    #+#             */
/*   Updated: 2026/07/08 12:29:47 by rcamps-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/main.h"

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

int	main(int argc, char **argv)
{
	char	**args;

	if (argc != 9)
	{
		printf("Error! 8 parameters are needed. The program runs like this:\n");
		printf("$> ./codexion <number_of_coders> <time_to_burnout> ");
		printf("<time_to_compile> <time_to_debug> <time_to_refactor> ");
		printf("<number_of_compiles_required> <dongle_cooldown> <scheduler>");
		return (1);
	}
	args = remove_first_arg(argv);
	while (*args)
		printf("%s\n", *args++);
	return (0);
}
