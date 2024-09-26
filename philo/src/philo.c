/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:34:24 by maweiss           #+#    #+#             */
/*   Updated: 2024/09/26 18:56:40 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void *ft_spawn_philo(void *arg)
{
	t_philo *philo;

	philo = (struct t_philo *) arg;

	
}

int	ft_philo_handler(t_philo *philo)
{
	int	i;

	i = 0;
	while(i < philo->nb_philo)
		pthread_create(philo->threads[i], NULL, ft_spawn_philo, philo)

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
	if (argc < 6)
		philo->nbotte_present = false;
	else
	{
		philo->nbotte_present = true;
		philo->nbotte = ft_atoi(argv[5]);
	}
	philo->threads = malloc(sizeof(pthread_t *) * (philo->nb_philo + 1));
	i = 0;
	while(i <= philo->nb_philo)
		philo->threads[i] = NULL;
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
	}
	return (0);
}
