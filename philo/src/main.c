/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:37:58 by maweiss           #+#    #+#             */
/*   Updated: 2024/10/09 12:38:32 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_general			main;

	printf("./philo nb_philo ttd tte tts nbotte\n");
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
