/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:39:01 by maweiss           #+#    #+#             */
/*   Updated: 2024/10/09 12:39:47 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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
	long long		elapsed_time;

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
