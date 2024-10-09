/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:42:16 by maweiss           #+#    #+#             */
/*   Updated: 2024/10/09 13:44:56 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_destroy_mutexes(t_general *main)
{
	int		i;
	int		ttw;

	i = 0;
	if (main->ttd2 > main->tts2)
		ttw = main->ttd2;
	else
		ttw = main->tts2;
	if (ttw < main->tte2)
		ttw = main->tte2;
	precise_sleep(ttw);
	pthread_mutex_unlock(&main->death);
	pthread_mutex_destroy(&main->death);
	pthread_mutex_destroy(&main->print);
	while (i < main->nb_philo)
	{
		pthread_mutex_destroy(&main->philos[i]->right_fork);
		pthread_mutex_destroy(&main->philos[i]->meal_count);
		pthread_mutex_destroy(&main->philos[i]->time);
		i++;
	}
	return (0);
}

void	ft_cleanup_philo(t_general *main)
{
	int	i;

	i = 0;
	ft_destroy_mutexes(main);
	while (i < main->nb_philo)
	{
		free(main->philos[i]);
		free(main->thread_return[i]);
		free(main->threads[i]);
		i++;
	}
	free(main->philos);
	free(main->thread_return);
	free(main->threads);
}
