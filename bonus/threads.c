/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerope200 <jerope200@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:16:46 by jesroble          #+#    #+#             */
/*   Updated: 2024/11/05 11:56:08 by jerope200        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	philo_eats_even(t_philo *phi)
{
	t_rules	*rules;

	rules = phi->rules;
	sem_wait(rules->fork);
	print_moment(rules, phi->philo_id, "has taken left fork");
	sem_wait(rules->fork);
	print_moment(rules, phi->philo_id, "has taken right fork");
	print_moment(rules, phi->philo_id, "is eating");
	phi->time_last_eat = timestamp();
	sem_wait(rules->meal_count);
	phi->times_ate++;
	if (phi->times_ate == rules->nb_eat)
		rules->philo_feed++;
	if (rules->philo_feed == rules->nb_philo)
		rules->all_ate = true;
	sem_post(rules->meal_count);
	wait_time(rules, rules->time_to_eat);
	sem_post(rules->fork);
	sem_post(rules->fork);
}

static void	philo_eats_odd(t_philo *phi)
{
	t_rules	*rules;

	rules = phi->rules;
	sem_wait(rules->fork);
	print_moment(rules, phi->philo_id, "has taken right fork");
	sem_wait(rules->fork);
	print_moment(rules, phi->philo_id, "has taken left fork");
	print_moment(rules, phi->philo_id, "is eating");
	phi->time_last_eat = timestamp();
	sem_wait(rules->meal_count);
	phi->times_ate++;
	if (phi->times_ate == rules->nb_eat)
		rules->philo_feed++;
	if (rules->philo_feed == rules->nb_philo)
		rules->all_ate = true;
	sem_post(rules->meal_count);
	wait_time(rules, rules->time_to_eat);
	sem_post(rules->fork);
	sem_post(rules->fork);
}

void	*philo_thread(void *philosopher)
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
		if (phi->philo_id % 2 == 0)
			philo_eats_even(phi);
		else if (phi->philo_id != 0)
			philo_eats_odd(phi);
		if (rules->died || rules->all_ate)
			break ;
		print_moment(rules, phi->philo_id, "is sleeping");
		wait_time(rules, rules->time_sleep);
	}
	return (NULL);
}

void	death_seeker(t_rules *rules, t_philo *p)
{
	int		i;

	while (!rules->all_ate)
	{
		i = -1;
		while (++i < rules->nb_philo && !rules->died)
		{
			sem_wait(rules->eating);
			if (time_taken(p[i].time_last_eat, timestamp()) > rules->time_death)
			{
				print_moment(rules, i, "died");
				rules->died = true;
			}
			sem_post(rules->eating);
			usleep(100);
		}
		if (rules->died)
			break ;
		usleep(100);
	}
}

void	finisher(t_rules *rules)
{
	int	i;

	i = -1;
	while (++i < rules->nb_philo)
		pthread_join(rules->philo[i].thread_id, NULL);
	i = -1;
	while (++i < rules->nb_philo) //esta linea hay que borrarla
		printf("total %d meals: %d\n", i, rules->philo[i].times_ate);
	sem_close(rules->fork);
	sem_close(rules->meal_count);
	sem_close(rules->write);
	sem_close(rules->eating);
	sem_unlink("/fork");
	sem_unlink("/meal_count");
	sem_unlink("/write");
	sem_unlink("/eating");
}
