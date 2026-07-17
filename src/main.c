/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamps-v <rcamps-v@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 12:54:44 by rcamps-v          #+#    #+#             */
/*   Updated: 2026/07/16 13:56:06 by rcamps-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/main.h"

int	main(int argc, char **argv)
{
	t_data	*parsed_data;

	parsed_data = NULL;
	parse_args(argc, argv, parsed_data);
	return (0);
}
