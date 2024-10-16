/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:36:24 by maweiss           #+#    #+#             */
/*   Updated: 2024/10/16 17:41:32 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>

enum e_meal
{
	eating,
	sleeping,
	thinking
};

typedef struct s_general	t_general;

typedef struct s_philosopher
{
	int						philo_nb;
	long long				startup_time;
	long					last_meal_time;
	long					nbothe;
	t_general				*main;
	pthread_mutex_t			right_fork;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			meal_count;
	pthread_mutex_t			time;
}				t_philosopher;

typedef struct s_general
{
	int				nb_philo;
	int				ttd;
	int				ttd2;
	int				tte;
	int				tte2;
	int				tts;
	int				tts2;
	int				nbotte;
	bool			nbotte_present;
	pthread_t		**threads;
	void			**thread_return;
	int				philos_spawned;
	long long		startup_time;
	bool			death_occured;
	t_philosopher	**philos;
	pthread_mutex_t	death;
	pthread_mutex_t	print;
}				t_general;

/* function prototypes*/
/* init.c */

int			ft_init_mutexes(t_general *main);
int			ft_input_precheck(char **argv, int args);
int			ft_allocate_philos(t_general *main);
int			ft_allocate(t_general *main);
int			ft_init_philo(t_general *main, int argc, char **argv);

/* ft_atoi.c */

int			ft_atoi(const char *nptr);

/* monitor.c */

int			ft_death_monitor(t_general *main, int i);
void		ft_meal_monitor(t_general *main, int i, int *nbothe_min);
int			ft_monitor(t_general *main);
int			ft_philo_handler(t_general *main);

/* philo.c */

void		*ft_philo(void *arg);
int			ft_monitor(t_general *main);
int			ft_philo_handler(t_general *main);

/* clean.c */

int			ft_destroy_mutexes(t_general *main);
void		ft_cleanup_philo(t_general *main);

/* sleep.c */

long long	current_time(void);
void		precise_sleep(int ms);

#endif
