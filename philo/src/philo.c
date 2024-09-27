/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:34:24 by maweiss           #+#    #+#             */
/*   Updated: 2024/09/27 11:45:59 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void ft_cleanup_philo(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->nb_philo)
	{
		free(philo->thread_return[i]);
		free(philo->threads[i]);
		i++;
	}
	free(philo->thread_return);
	free(philo->threads);

}


void *ft_spawn_philo(void *arg)
{
	static int		i;
	t_philo			*philo;

	philo = (t_philo *) arg;
	if (philo->philos_spawned == 0)
	i = 0;
	else if (philo->philos_spawned > 0)
		i++;
	printf("I am Philo number %d\n", i);
	usleep(500);
	return (NULL);
}

int	ft_philo_handler(t_philo *philo)
{
	int	i;

	i = 0;
	while(i < philo->nb_philo)
	{
		philo->philos_spawned++;
		pthread_create(philo->threads[i++], NULL, ft_spawn_philo, philo);
	}
	i = 0;
	while(i < philo->nb_philo)
	{
		pthread_join(*philo->threads[i], philo->thread_return[i]);
		i++;
	}
	return (0);
}

int	ft_init_philo(t_philo *philo, int argc, char **argv)
{
	int	i;

	philo->nb_philo = ft_atoi(argv[1]);
	if (philo->nb_philo < 1)
		return (-1);
	philo->ttd = ft_atoi(argv[2]);
	philo->tte = ft_atoi(argv[3]);
	philo->tts = ft_atoi(argv[4]);
	philo->philos_spawned = 0;
	if (argc < 6)
		philo->nbotte_present = false;
	else
	{
		philo->nbotte_present = true;
		philo->nbotte = ft_atoi(argv[5]);
	}
	philo->threads = malloc(sizeof(pthread_t *) * (philo->nb_philo + 1));
	philo->thread_return = malloc(sizeof(void *) * (philo->nb_philo + 1));
	i = 0;
	while(i < philo->nb_philo)
	{
		philo->threads[i] = malloc(sizeof(pthread_t) * 1);
		philo->thread_return[i++] = NULL;
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_philo		philo;

	if (argc != 5 && argc != 6)
	{
		printf("Error: wrong number of arguments!\n");
		return (1);
	}
	else
	{
		ft_init_philo(&philo, argc, argv);
		ft_philo_handler(&philo);
		ft_cleanup_philo(&philo);
	}
	return (0);
}
