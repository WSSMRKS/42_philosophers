/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:37:58 by maweiss           #+#    #+#             */
/*   Updated: 2024/10/09 14:42:08 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_general			main;
	int					ret;

	if ((argc != 5 && argc != 6) || ft_init_philo(&main, argc, argv) == -1)
	{
		printf("Error: input error\n");
		return (5);
	}
	if (main.nb_philo == 1)
	{
		precise_sleep(main.ttd);
		printf("%d 1 died", main.ttd);
		ret = 1;
	}
	else
		ret = ft_philo_handler(&main);
	ft_cleanup_philo(&main);
	return (ret);
}
