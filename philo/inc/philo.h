/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:36:24 by maweiss           #+#    #+#             */
/*   Updated: 2024/09/26 18:18:36 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_philo {
	int			nb_philo;
	int			ttd;
	int			tte;
	int			tts;
	int			nbotte;
	bool		nbotte_present;
	pthread_t	**threads;
}				t_philo;

/* function prototypes*/
int	ft_atoi(const char *nptr);


#endif
