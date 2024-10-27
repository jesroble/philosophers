/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesroble <jesroble@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:58:37 by jesroble          #+#    #+#             */
/*   Updated: 2024/10/25 11:15:37 by jesroble         ###   ########.fr       */
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
	pthread_mutex_lock(&(rules->write));
	if (!(rules->died))
	{
		printf("%lli	", (timestamp() - rules->first_timestamp));
		printf("%i	", id);
		printf("%s	\n", action);
	}
	pthread_mutex_unlock(&(rules->write));
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
