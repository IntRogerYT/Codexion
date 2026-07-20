/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamps-v <rcamps-v@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 13:40:10 by rcamps-v          #+#    #+#             */
/*   Updated: 2026/07/20 14:19:13 by rcamps-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
/********************************/
/*        EXTERN LIBS           */
/********************************/
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <limits.h>
/********************************/
/*           MACROS             */
/********************************/

/********************************/
/*          VARIABLES           */
/********************************/

/********************************/
/*           STRUCTS            */
/********************************/
typedef enum e_scheduler
{
	FIFO,
	EDF,
}	t_scheduler;

typedef struct s_request
{
	unsigned int	coder_id;
	long			deadline;
	unsigned int	arrival_order;
}	t_request;

typedef struct s_node
{
	t_request		req;
	struct s_node	*next;
}	t_node;

typedef struct s_queue
{
	t_node	*head;
	int		size;
	int		(*cmp)(t_request, t_request);
}	t_queue;

typedef struct s_dongle
{
	bool			available;
	unsigned int	last_release_ms;
	t_queue			wait_queue;
}	t_dongle;

typedef struct s_coder
{
	unsigned int	id;
	unsigned int	compiles_done;
	unsigned int	last_compile_ms;
	t_dongle		*left;
	t_dongle		*right;
	int				left_idx;
	int				right_idx;
	struct s_data	*data;
}	t_coder;

typedef struct s_data
{
	unsigned int	number_of_coders;
	unsigned int	time_to_burnout;
	unsigned int	time_to_compile;
	unsigned int	time_to_debug;
	unsigned int	time_to_refactor;
	unsigned int	number_of_compiles_required;
	unsigned int	dongle_cooldown;
	t_scheduler		scheduler;
	t_coder			*coders;
	t_dongle		*dongles;
	bool			running;
	unsigned long	start_time;
	unsigned long	request_counter;
}	t_data;
/********************************/
/*          FUNCTIONS           */
/********************************/
//========== main.c ==========
int		main(int argc, char **argv);
//========= parse_and_validation/ =========
void	parse_args(int argc, char **argv, t_data *data);
void	validate_args(char **args, t_data *data);
//========== utils/ ==========
int		ft_isnumber(const char *str);
int		ft_strisalpha(char *s);
void	error(char *message);
void	free_error(char **args, t_data *data, char *message);
void	free_matrix(char **matrix);
#endif
