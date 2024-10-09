/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:34:24 by maweiss           #+#    #+#             */
/*   Updated: 2024/10/09 12:47:11 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*ft_spawn_philo(void *arg)
{
	t_philosopher		*philo;
	long long			timestamp;
	int					i;

	philo = (t_philosopher *) arg;
	i = 0;
	while (1)
	{

		if (((philo->philo_nb) & 1) == 0)
		{
			pthread_mutex_lock(&philo->right_fork);
			pthread_mutex_lock(philo->left_fork);
		}
		else
		{
			pthread_mutex_lock(philo->left_fork);
			pthread_mutex_lock(&philo->right_fork);
		}
		pthread_mutex_lock(&philo->time);
		philo->last_meal_time = current_time();
		pthread_mutex_unlock(&philo->time);
		pthread_mutex_lock(&philo->main->death);
		if (philo->main->death_occured == true)
		{
			pthread_mutex_unlock(&philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(&philo->main->death);
			return (0);
		}
		pthread_mutex_unlock(&philo->main->death);
		pthread_mutex_lock(&philo->main->print);
		timestamp = current_time() - philo->startup_time;
		printf("%lld %d is eating\n", timestamp, philo->philo_nb);
		pthread_mutex_unlock(&philo->main->print);
		precise_sleep(philo->main->tte);
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_lock(&philo->meal_count);
		philo->nbothe++;
		pthread_mutex_unlock(&philo->meal_count);
		pthread_mutex_lock(&philo->main->death);
		if (philo->main->death_occured == true)
		{
			pthread_mutex_unlock(&philo->main->death);
			return (0);
		}
		pthread_mutex_unlock(&philo->main->death);
		pthread_mutex_lock(&philo->main->print);
		timestamp = current_time() - philo->startup_time;
		printf("%lld %d is sleeping\n", timestamp, philo->philo_nb);
		pthread_mutex_unlock(&philo->main->print);
		precise_sleep(philo->main->tts);
		pthread_mutex_lock(&philo->main->death);
		if (philo->main->death_occured == true)
		{
			pthread_mutex_unlock(&philo->main->death);
			return (0);
		}
		pthread_mutex_unlock(&philo->main->death);
		pthread_mutex_lock(&philo->main->print);
		timestamp = current_time() - philo->startup_time;
		printf("%lld %d is thinking\n", timestamp, philo->philo_nb);
		pthread_mutex_unlock(&philo->main->print);
		i++;
	}
	return (NULL);
}

int	ft_monitor(t_general *main)
{
	int			i;
	int			nbothe_min;
	long long	timestamp;


	while (1)
	{
		i = 0;
		while (i < main->nb_philo)
		{
			precise_sleep(5);
			nbothe_min = INT_MAX;
			if (main->nbotte_present == true)
			{
				pthread_mutex_lock(&main->philos[i]->meal_count);
				if (main->philos[i]->nbothe < nbothe_min)
					nbothe_min = main->philos[i]->nbothe;
				pthread_mutex_unlock(&main->philos[i]->meal_count);
			}
			pthread_mutex_lock(&main->philos[i]->time);
			if (current_time() - main->philos[i]->last_meal_time > main->ttd)
			{
				timestamp = current_time() - main->startup_time;
				pthread_mutex_lock(&main->print);
				printf("%lld %d died\n", timestamp, i+1);
				pthread_mutex_lock(&main->death);
				main->death_occured = true;
				printf("death detected\n");
				pthread_mutex_unlock(&main->print);
				pthread_mutex_unlock(&main->death);
				return (1);
			}
			pthread_mutex_unlock(&main->philos[i]->time);
			i++;
		}
		if (main->nbotte_present == true && nbothe_min >= main->nbotte)
		{
			pthread_mutex_lock(&main->death);
			return (0);
		}
	}
}


int	ft_philo_handler(t_general *main)
{
	int		i;

	i = 0;
	while (i < main->nb_philo)
	{
		main->philos_spawned++;
		main->philos[i]->philo_nb = main->philos_spawned;
		pthread_create(main->threads[i], NULL, ft_spawn_philo, main->philos[i]);
		i++;
	}
	if (ft_monitor(main) == 0)
		printf("\"number_of_times_each_philosopher_must_eat\" reached\n");
	i = 0;
	while (i < main->nb_philo)
		pthread_detach(*main->threads[i++]);
	return (0);
}
