/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerope200 <jerope200@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:58:37 by jesroble          #+#    #+#             */
/*   Updated: 2024/11/05 11:46:49 by jerope200        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(char *n)
{
	int	result;

	result = 0;
	while ((*n >= 9 && *n <= 13) || *n == 32)
		n++;
	if (*n == '-')
		return (-1);
	if (*n == '+')
		n++;
	while (*n)
	{
		if (*n >= '0' && *n <= '9')
		{
			result = result * 10 + (*n - '0');
			n++;
		}
		else
			return (-1);
	}
	return (result);
}

void	print_moment(t_rules *rules, int id, char *action)
{
	sem_wait(rules->write);
	if (!(rules->died))
	{
		ft_printf("%i	", (timestamp() - rules->first_timestamp));
		ft_printf("%i	", id);
		ft_printf("%s	\n", action);
	}
	sem_post(rules->write);
	return ;
}

void	wait_time(t_rules *rules, int time_needed)
{
	int	time;

	time = timestamp();
	while (!rules->died)
	{
		if (time_taken(time, timestamp()) >= time_needed)
			break ;
		usleep(300);
	}
}

long long	time_taken(long long past, long long present)
{
	return (present - past);
}

long long	timestamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
