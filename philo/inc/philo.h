/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:36:24 by maweiss           #+#    #+#             */
/*   Updated: 2024/10/01 21:00:57 by maweiss          ###   ########.fr       */
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

typedef struct s_general t_general;

// typedef struct s_surveillance {
// 	t_general			*main;
// }				t_surveillance;

typedef struct s_philosopher {
	int						philo_nb;
	long long				startup_time;		//local startup time;
	long					last_meal_time;		//MUTEX
	long					nbothe;				//Number of times has eaten
	t_general				*main;
	pthread_mutex_t			right_fork;			//MUTEX
	pthread_mutex_t			*left_fork;			//MUTEX
	pthread_mutex_t			state;
	pthread_mutex_t			time;
}				t_philosopher;

typedef struct s_general {
	int				nb_philo;
	int				ttd;						//Time to die;
	int				tte;						//Time to eat;
	int				tts;						//Time to sleep;
	int				nbotte;						//Number of times to eat;
	bool			nbotte_present;				//Number of times to eat Present?;
	pthread_t		**threads;
	void			**thread_return;
	int				philos_spawned;
	long long		startup_time;
	t_philosopher	**philos;
	// t_surveillance	big_brother;
	pthread_mutex_t	death;
	// pthread_mutex_t	print;
}				t_general;

/* function prototypes*/
/* ft_atoi.c */

int	ft_atoi(const char *nptr);

/*philo.c*/

void		ft_cleanup_philo(t_general *main);
void		*ft_spawn_philo(void *arg);
int			ft_philo_handler(t_general *main);
int			ft_init_mutexes(t_general *main);
int			ft_init_philo(t_general *main, int argc, char **argv);
long long	current_time(void);
void		precise_sleep(int ms);
int	ft_destroy_mutexes(t_general *main);

#endif
