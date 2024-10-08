/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 12:25:26 by maweiss           #+#    #+#             */
/*   Updated: 2024/10/09 13:35:31 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_core(const char *str)
{
	int	i;
	int	digits;
	int	nb;

	i = 1;
	digits = 1;
	nb = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		digits *= 10;
		i++;
	}
	i = 0;
	while (digits > 0)
	{
		nb = nb + (str[i] - '0') * digits;
		digits /= 10;
		i++;
	}
	return (nb);
}

int	ft_atoi(const char *nptr)
{
	int		sign;

	sign = 1;
	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\v' || *nptr == '\r'
		|| *nptr == '\n' || *nptr == '\f')
		nptr++;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr == '0' && *(nptr + 1) == '0')
		nptr++;
	if (*nptr >= '0' && *nptr <= '9')
		return (ft_core(nptr) * sign);
	else
		return (0);
}
