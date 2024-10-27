/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesroble <jesroble@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:16:46 by jesroble          #+#    #+#             */
/*   Updated: 2024/10/27 21:26:37 by jesroble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	philo_eats(t_philo *phi)
{
	t_rules	*rules;

	rules = phi->rules;
	pthread_mutex_lock(&(rules->fork[phi->left_fork_id]));
	print_moment(rules, phi->philo_id, "has taken left fork");
	pthread_mutex_lock(&(rules->fork[phi->right_fork_id]));
	print_moment(rules, phi->philo_id, "has taken right fork");
	print_moment(rules, phi->philo_id, "is eating");
	phi->time_last_eat = timestamp();
	pthread_mutex_lock(&(rules->meal_count_mutex));
	phi->times_ate++;
	if (phi->times_ate == rules->nb_eat)
		rules->philo_feed++;
	if (rules->philo_feed == rules->nb_philo)
		rules->all_ate = true;
	pthread_mutex_unlock(&(rules->meal_count_mutex));
	wait_time(rules, rules->time_to_eat);
	pthread_mutex_unlock(&(rules->fork[phi->left_fork_id]));
	pthread_mutex_unlock(&(rules->fork[phi->right_fork_id]));
}

static void	*philo_thread(void *philosopher)
{
	t_philo			*phi;
	t_rules			*rules;
	unsigned long	fruit;

	phi = (t_philo *)philosopher;
	rules = phi->rules;
	if (phi->philo_id % 2 == 0)
		usleep(200);
	fruit = fruit_generator(timestamp(), phi->philo_id);
	while (1)
	{
		if (rules->died || rules->all_ate)
			break ;
		print_moment(rules, phi->philo_id, "is thinking");
		usleep(my_rand(fruit) % 1000);
		philo_eats(phi);
		if (rules->died || rules->all_ate)
			break ;
		print_moment(rules, phi->philo_id, "is sleeping");
		wait_time(rules, rules->time_sleep);
	}
	//printf("Philosopher %d finished thread.\n", phi->philo_id);
	return (NULL);
}

static void	death_seeker(t_rules *rules, t_philo *p)
{
	int		i;

	while (!rules->all_ate)
	{
		i = -1;
		while (++i < rules->nb_philo && !rules->died)
		{
			pthread_mutex_lock(&(rules->eating));
			//printf("Checking philosopher %d, last meal time: %llu\n", i, p[i].time_last_eat);
			if (time_taken(p[i].time_last_eat, timestamp()) > rules->time_death)
			{
				print_moment(rules, i, "died");
				rules->died = true;
				//printf("Philosopher %d has died.\n", i);
			}
			pthread_mutex_unlock(&(rules->eating));
			usleep(100);
		}
		if (rules->died)
			break ;
		usleep(100);
	}
	//printf("Death seeker finished. All ate: %d, Died: %d\n", rules->all_ate, rules->died);
}

static void	finisher(t_rules *rules)
{
	int	i;

	i = -1;
	while (++i < rules->nb_philo)
		pthread_join(rules->philo[i].thread_id, NULL);
	i = -1;
	while (++i < rules->nb_philo)
		printf("total %d meals: %d\n", i, rules->philo[i].times_ate);
	i = -1;
	while (++i < rules->nb_philo)
		pthread_mutex_destroy(&rules->fork[i]);
	pthread_mutex_destroy(&rules->meal_count_mutex);
	pthread_mutex_destroy(&rules->write);
	pthread_mutex_destroy(&rules->eating);
}

bool	launcher(t_rules *rules)
{
	int		i;
	t_philo	*phi;

	i = 0;
	phi = rules->philo;
	ft_printf("    Time     Philosopher       Action\n\n");
	rules->first_timestamp = timestamp();
	while (i < rules->nb_philo)
	{
		if (pthread_create(&(phi[i].thread_id), NULL, philo_thread, &(phi[i])))
			error_msg("something went wrong creating the threads");
		phi[i].time_last_eat = timestamp();
		i++;
	}
	death_seeker(rules, rules->philo);
	finisher(rules);
	return (true);
}
