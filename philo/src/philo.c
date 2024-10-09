/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:34:24 by maweiss           #+#    #+#             */
/*   Updated: 2024/10/09 18:40:21 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_pickup_forks(t_philosopher *philo)
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
}

int	ft_death_check(t_philosopher *philo, int meal_check)
{
	pthread_mutex_lock(&philo->main->death);
	if (philo->main->death_occured == true)
	{
		if (meal_check == 1)
		{
			pthread_mutex_unlock(&philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
		}
		pthread_mutex_unlock(&philo->main->death);
		return (1);
	}
	pthread_mutex_unlock(&philo->main->death);
	return (0);
}

void	ft_print_statement(t_philosopher *philo, int type)
{
	long long			timestamp;

	pthread_mutex_lock(&philo->main->print);
	timestamp = current_time() - philo->startup_time;
	if (type == eating)
		printf("%lld %d is eating\n", timestamp, philo->philo_nb);
	else if (type == sleeping)
		printf("%lld %d is sleeping\n", timestamp, philo->philo_nb);
	else
		printf("%lld %d is thinking\n", timestamp, philo->philo_nb);
	pthread_mutex_unlock(&philo->main->print);
}

void	ft_count_meal(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->time);
	philo->last_meal_time = current_time();
	pthread_mutex_unlock(&philo->time);
}

void	*ft_philo(void *arg)
{
	t_philosopher		*philo;

	philo = (t_philosopher *) arg;
	while (1)
	{
		ft_pickup_forks(philo);
		ft_count_meal(philo);
		if (ft_death_check(philo, 1) == 1)
			return (NULL);
		ft_print_statement(philo, eating);
		precise_sleep(philo->main->tte);
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_lock(&philo->meal_count);
		philo->nbothe++;
		pthread_mutex_unlock(&philo->meal_count);
		if (ft_death_check(philo, 1) == 1)
			return (NULL);
		ft_print_statement(philo, sleeping);
		precise_sleep(philo->main->tts);
		if (ft_death_check(philo, 1) == 1)
			return (NULL);
		ft_print_statement(philo, thinking);
	}
}
