/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerope200 <jerope200@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 20:23:15 by jesroble          #+#    #+#             */
/*   Updated: 2024/11/17 13:23:44 by jerope200        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_mutex(t_rules *rules)
{
	int	i;

	i = rules->nb_philo;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(rules->fork[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(rules->meal_count_mutex), NULL))
		return (1);
	if (pthread_mutex_init(&(rules->write), NULL))
		return (1);
	if (pthread_mutex_init(&(rules->eating), NULL))
		return (1);
	return (0);
}

static void	init_philo(t_rules *rules)
{
	t_philo	*philo;
	int		i;

	philo = rules->philo;
	i = rules->nb_philo;
	while (i--)
	{
		philo[i].philo_id = i;
		philo[i].left_fork_id = i;
		philo[i].right_fork_id = (i + 1) % rules->nb_philo;
		philo[i].times_ate = 0;
		philo[i].time_last_eat = 0;
		philo[i].rules = rules;
	}
}

bool	ft_init_rules(t_rules *rules, char **av)
{
	rules->nb_philo = ft_atoi(av[1]);
	rules->time_death = ft_atoi(av[2]);
	rules->time_to_eat = ft_atoi(av[3]);
	rules->time_sleep = ft_atoi(av[4]);
	if (rules->nb_philo < 1 || rules->time_death < 1 \
	|| rules->time_to_eat < 1 || rules->time_sleep < 1)
		error_msg("not working values");
	if (av[5])
	{
		rules->nb_eat = ft_atoi(av[5]);
		if (rules->nb_eat <= 0)
			error_msg("not working values");
	}
	else
		rules->nb_eat = -1;
	rules->philo_feed = 0;
	rules->all_ate = false;
	rules->died = false;
	init_mutex(rules);
	init_philo(rules);
	return (true);
}
