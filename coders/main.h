/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamps-v <rcamps-v@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 13:40:10 by rcamps-v          #+#    #+#             */
/*   Updated: 2026/08/26 11:46:14 by rcamps-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
/********************************/
/*        EXTERN LIBS           */
/********************************/
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
/********************************/
/*           MACROS             */
/********************************/

/********************************/
/*          VARIABLES           */
/********************************/

/********************************/
/*           STRUCTS            */
/********************************/
typedef enum e_state
{
	TAKEN_DONGLE,
	COMPILING,
	DEBUGGING,
	REFACTORING,
	BURNED_OUT
}	t_state;

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
	unsigned int	id;
	bool			available;
	unsigned long	last_release_ms;
	t_queue			wait_queue;
	pthread_mutex_t	lock;
	pthread_cond_t	cond;
	bool			ready;
}	t_dongle;

typedef struct s_coder
{
	unsigned int	id;
	unsigned int	compiles_done;
	unsigned long	last_compile_ms;
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
	pthread_mutex_t	log_lock;
	bool			log_lock_ready;
	pthread_mutex_t	sim_lock;
	bool			sim_lock_ready;
	pthread_t		*threads;
	pthread_t		monitor;
}	t_data;
/********************************/
/*          FUNCTIONS           */
/********************************/
//========== main.c ==========
int				main(int argc, char **argv);
//========= parse_and_validation/ =========
void			parse_args(int argc, char **argv, t_data *data);
void			validate_args(char **args, t_data *data);
//========== init_data/ ==========
void			init_data(t_data *data);
int				init_dongle(t_dongle *dongle, unsigned int i, t_data *data);
void			init_coder(t_coder *coder, unsigned int i, t_data *data);
void			assign_dongles(t_coder *coder, unsigned int i, t_data *data);
//========== logging/ ==========
unsigned long	current_ms(void);
unsigned long	get_elapsed_ms(t_data *data);
void			log_status(t_data *data, unsigned int coder_id, t_state state);
//========== simulation/ ==========
void			*routine(void *arg);
bool			get_running(t_data *data);
void			set_running(t_data *data, bool value);
unsigned long	get_last_compile(t_coder *coder);
void			set_last_compile(t_coder *coder, unsigned long value);
unsigned int	get_compiles_done(t_coder *coder);
void			inc_compiles_done(t_coder *coder);
int				acquire_dongle(t_dongle *dongle, t_coder *coder);
void			release_dongle(t_dongle *dongle);
int				acquire_both_dongles(t_coder *coder);
void			release_both_dongles(t_coder *coder);
void			run_simulation(t_data *data);
void			*monitor_routine(void *arg);
void			coders_loop(t_data *data, unsigned int *finished_coders);
int				cmp_fifo(t_request a, t_request b);
int				cmp_edf(t_request a, t_request b);
void			queue_push(t_queue *queue, t_request req);
t_request		queue_pop(t_queue *queue);
//========== utils/ ==========
int				ft_isnumber(const char *str);
int				ft_strisalpha(char *s);
void			error(char *message);
void			free_error(char **args, t_data *data, char *message);
void			free_matrix(char **matrix);
void			cleanup(t_data *data, char *message);
#endif
