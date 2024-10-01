/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:34:24 by maweiss           #+#    #+#             */
/*   Updated: 2024/10/01 18:55:13 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void ft_cleanup_philo(t_general *main)
{
	int	i;

	i = 0;
	while (i < main->nb_philo)
	{
		free(main->thread_return[i]);
		free(main->threads[i]);
		i++;
	}
	free(main->thread_return);
	free(main->threads);

}


void *ft_spawn_philo(void *arg)
{
	t_philosopher		*philo;
	long long			timestamp;

	philo = (t_philosopher *) arg;
	// usleep(5000);
	printf("I am Philo number %d\n", philo->philo_nb);
	// if (philo->forks->fork[i] == false)
	// 	philo

	while(1)
	{
		pthread_mutex_lock(&philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
		timestamp = current_time() - philo->startup_time;
		printf("%lld %d is eating\n", timestamp, philo->philo_nb);
		precise_sleep(philo->main->tte);
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		timestamp = current_time() - philo->startup_time;
		printf("%lld %d is sleeping\n", timestamp, philo->philo_nb);
		precise_sleep(philo->main->tts);
		timestamp = current_time() - philo->startup_time;
		printf("%lld %d is thinking\n", timestamp, philo->philo_nb);
	}
	return (NULL);
}

int	ft_philo_handler(t_general *main)
{
	int		i;
	// void	*retval;

	i = 0;
	while(i < main->nb_philo)
	{
		main->philos_spawned++;
		main->philos[i]->philo_nb = main->philos_spawned;
		pthread_create(main->threads[i], NULL, ft_spawn_philo, main->philos[i]);
		i++;
	}
	

	i = 0;
	while(i < main->nb_philo)
	{
		pthread_join(*main->threads[i], &main->thread_return[i]);
		printf("retval of the thread is %d\n", (int) (intptr_t) main->thread_return[i]);
		i++;
	}
	return (0);
}

int	ft_init_mutexes(t_general *main)
{
	int i;

	i = 0;
	pthread_mutex_init(&main->death, NULL);
	while (i < main->nb_philo)
	{
		if (i > 0)
			main->philos[i]->left_fork = &main->philos[i - 1]->right_fork;
		else
			main->philos[i]->left_fork = &main->philos[main->nb_philo - 1]->right_fork;
		pthread_mutex_init(&main->philos[i]->right_fork, NULL);
		pthread_mutex_init(&main->philos[i]->state, NULL);
		pthread_mutex_init(&main->philos[i]->time, NULL);
		i++;
	}
	return (0);
}

int	ft_init_philo(t_general *main, int argc, char **argv)
{
	int				i;
	int				j;

	i = 1;
	while (i < 5)
	{
		j = 0;
		while(argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9' || j > 9)
				return (-1);
			j++;
		}
		i++;
	}
	main->nb_philo = ft_atoi(argv[1]);
	if (main->nb_philo < 1)
		return (-1);
	main->ttd = ft_atoi(argv[2]);
	main->tte = ft_atoi(argv[3]);
	main->tts = ft_atoi(argv[4]);
	main->philos_spawned = 0;
	if (argc < 6)
		main->nbotte_present = false;
	else
	{
		main->nbotte_present = true;
		main->nbotte = ft_atoi(argv[5]);
	}
	main->threads = malloc(sizeof(pthread_t *) * (main->nb_philo + 1));
	main->thread_return = malloc(sizeof(void *) * (main->nb_philo + 1));
	i = 0;
	main->philos = malloc(sizeof(t_philosopher *) * (main->nb_philo + 1));
	i = 0;
	main->startup_time = current_time();
	while(i < main->nb_philo)
	{
		main->threads[i] = malloc(sizeof(pthread_t) * 1);
		main->thread_return[i] = NULL;
		main->philos[i] = malloc(sizeof(t_philosopher) * 1);
		main->philos[i]->main = main;
		main->philos[i]->startup_time = main->startup_time;
		i++;
	}
	main->threads[i] = NULL;
	main->philos[i] = NULL;
	ft_init_mutexes(main);
	return (0);
}

int main(int argc, char **argv)
{
	t_general			main;

	printf("current time: %lld\n", current_time());
	if (argc != 5 && argc != 6)
	{
		printf("Error: input error\n");
		return (1);
	}
	else
	{
		if (ft_init_philo(&main, argc, argv) == -1)
		{
			printf("Error: input error\n");
			return (5);
		}
		ft_philo_handler(&main);
		ft_cleanup_philo(&main);
	}
	return (0);
}

long long	current_time(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

void	precise_sleep(int ms)
{
	struct timeval	start;
	struct timeval	end;
	long long	elapsed_time;
	elapsed_time = 0;
	gettimeofday(&start, NULL);
	while (elapsed_time < ms)
	{
		usleep(10);
		gettimeofday(&end, NULL);
		elapsed_time = (end.tv_sec - start.tv_sec) * 1000LL
			+ (end.tv_usec - start.tv_usec) / 1000;
	}
}
