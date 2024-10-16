/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:40:29 by maweiss           #+#    #+#             */
/*   Updated: 2024/10/16 18:42:13 by maweiss          ###   ########.fr       */
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

int	ft_input_precheck(char **argv, int args)
{
	int	i;
	int	j;

	i = 1;
	while (i < args)
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
	return (0);
}

int	ft_allocate_philos(t_general *main)
{
	int	i;

	i = 0;
	while (i < main->nb_philo)
	{
		main->threads[i] = malloc(sizeof(pthread_t) * 1);
		if (!main->threads[i])
			return (-1);
		main->thread_return[i] = NULL;
		main->philos[i] = malloc(sizeof(t_philosopher) * 1);
		if (!main->philos[i])
			return (-1);
		main->philos[i]->main = main;
		main->philos[i]->startup_time = main->startup_time;
		main->philos[i]->last_meal_time = main->startup_time;
		main->philos[i]->nbothe = 0;
		main->death_occured = false;
		i++;
	}
	main->threads[i] = NULL;
	main->philos[i] = NULL;
	return (0);
}

int	ft_allocate(t_general *main)
{
	main->threads = malloc(sizeof(pthread_t *) * (main->nb_philo + 1));
	if (!main->threads)
		return (-1);
	main->thread_return = malloc(sizeof(void *) * (main->nb_philo + 1));
	if (!main->thread_return)
		return (-1);
	main->philos = malloc(sizeof(t_philosopher *) * (main->nb_philo + 1));
	if (!main->philos)
		return (-1);
	if (!ft_allocate_philos(main))
		return (-1);
	return (0);
}

int	ft_init_philo(t_general *main, int argc, char **argv)
{
	if ((argc == 5 && ft_input_precheck(argv, 5) == -1)
		|| (argc == 6 && ft_input_precheck(argv, 6) == -1))
		return (-1);
	main->nb_philo = ft_atoi(argv[1]);
	main->ttd = ft_atoi(argv[2]);
	main->tte = ft_atoi(argv[3]);
	main->tts = ft_atoi(argv[4]);
	main->ttd2 = main->ttd;
	main->tts2 = main->tts;
	main->philos_spawned = 0;
	main->nbotte_present = false;
	if (argc == 6)
	{
		main->nbotte_present = true;
		main->nbotte = ft_atoi(argv[5]);
	}
	main->startup_time = current_time();
	if (main->nb_philo < 1 || !ft_allocate(main))
		return (-1);
	ft_init_mutexes(main);
	return (0);
}
