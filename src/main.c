/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamps-v <rcamps-v@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 12:54:44 by rcamps-v          #+#    #+#             */
/*   Updated: 2026/07/14 13:57:22 by rcamps-v         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/main.h"


int	main(int argc, char **argv)
{
	char	**args;
	t_data	parsed_data;

	parsed_data = parse_args(argc, argv, args);
	return (0);
}
