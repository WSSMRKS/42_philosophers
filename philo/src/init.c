/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:40:29 by maweiss           #+#    #+#             */
/*   Updated: 2024/10/09 12:43:17 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_init_mutexes(t_general *main)
{
	int	i;

	i = 0;
	pthread_mutex_init(&main->death, NULL);
	pthread_mutex_init(&main->print, NULL);
	while (i < main->nb_philo)
	{
		if (i > 0)
			main->philos[i]->left_fork = &main->philos[i - 1]->right_fork;
		else
			main->philos[i]->left_fork
				= &main->philos[main->nb_philo - 1]->right_fork;
		pthread_mutex_init(&main->philos[i]->right_fork, NULL);
		pthread_mutex_init(&main->philos[i]->meal_count, NULL);
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
		while (argv[i][j])
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
	main->ttd2 = main->ttd;
	main->tte2 = main->tte;
	main->tts2 = main->tts;
	main->philos_spawned = 0;
	if (argc < 6)
		main->nbotte_present = false;
	else
	{
		main->nbotte_present = true;
		j = 0;
		while (argv[5][j])
		{
			if (argv[5][j] < '0' || argv[5][j] > '9' || j > 9)
				return (-1);
			j++;
		}
		main->nbotte = ft_atoi(argv[5]);
	}
	main->threads = malloc(sizeof(pthread_t *) * (main->nb_philo + 1));
	main->thread_return = malloc(sizeof(void *) * (main->nb_philo + 1));
	i = 0;
	main->philos = malloc(sizeof(t_philosopher *) * (main->nb_philo + 1));
	i = 0;
	main->startup_time = current_time();
	while (i < main->nb_philo)
	{
		main->threads[i] = malloc(sizeof(pthread_t) * 1);
		main->thread_return[i] = NULL;
		main->philos[i] = malloc(sizeof(t_philosopher) * 1);
		main->philos[i]->main = main;
		main->philos[i]->startup_time = main->startup_time;
		main->philos[i]->last_meal_time = main->startup_time;
		main->philos[i]->nbothe = 0;
		main->death_occured = false;
		i++;
	}
	main->threads[i] = NULL;
	main->philos[i] = NULL;
	ft_init_mutexes(main);
	return (0);
}