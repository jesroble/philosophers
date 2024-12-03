/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerope200 <jerope200@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:28:56 by jesroble          #+#    #+#             */
/*   Updated: 2024/11/19 18:26:57 by jerope200        ###   ########.fr       */
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

void print_moment(t_rules *rules, int id, char *action)
{
 	pthread_mutex_lock(&(rules->write));
    if (!(rules->died || rules->all_ate))
    {
        printf("%-8lli       %-8i    %-20s\n",
               (timestamp() - rules->first_timestamp),
               id + 1, action);
    }
    pthread_mutex_unlock(&(rules->write));
}


void wait_time(t_rules *rules, int time_in_ms)
{
    long long start_time = timestamp();
    
    while (1)
    {
        pthread_mutex_lock(&(rules->meal_count_mutex));
        if (rules->died || time_taken(start_time, timestamp()) >= time_in_ms)
        {
            pthread_mutex_unlock(&(rules->meal_count_mutex));
            break;
        }
        pthread_mutex_unlock(&(rules->meal_count_mutex));
        usleep(100);
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