/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamps-v <rcamps-v@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 13:02:00 by rcamps-v          #+#    #+#             */
/*   Updated: 2026/08/26 13:02:00 by rcamps-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

void	inc_compiles_done(t_coder *coder)
{
	pthread_mutex_lock(&coder->data->sim_lock);
	coder->compiles_done++;
	pthread_mutex_unlock(&coder->data->sim_lock);
}
