/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerope200 <jerope200@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:16:18 by jesroble          #+#    #+#             */
/*   Updated: 2024/11/19 18:32:58 by jerope200        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void philo_alone(t_philo *phi)
{
    t_rules *rules;

    rules = phi->rules;
    pthread_mutex_lock(&(rules->fork[phi->left_fork_id]));
    print_moment(rules, phi->philo_id, "has taken left fork");
    wait_time(rules, rules->time_death);
    print_moment(rules, phi->philo_id, "died");
    rules->died = true;
    pthread_mutex_unlock(&(rules->fork[phi->left_fork_id]));
}

static void philo_eats(t_philo *phi)
{
    t_rules *rules;

    rules = phi->rules;
    pthread_mutex_lock(&(rules->fork[phi->left_fork_id]));
    print_moment(rules, phi->philo_id, "has taken left  fork");
    pthread_mutex_lock(&(rules->fork[phi->right_fork_id]));
    print_moment(rules, phi->philo_id, "has taken right fork");
    pthread_mutex_lock(&(rules->eating));
    print_moment(rules, phi->philo_id, "is eating");
    phi->time_last_eat = timestamp();
    pthread_mutex_unlock(&(rules->eating));
    wait_time(rules, rules->time_to_eat);
    pthread_mutex_lock(&(rules->meal_count_mutex));
    phi->times_ate++;
    if (phi->times_ate == rules->nb_eat)
        rules->philo_feed++;
    if (rules->philo_feed == rules->nb_philo)
        rules->all_ate = true;
    pthread_mutex_unlock(&(rules->meal_count_mutex));
    pthread_mutex_unlock(&(rules->fork[phi->left_fork_id]));
    pthread_mutex_unlock(&(rules->fork[phi->right_fork_id]));
}

void *philo_thread(void *philosopher)
{
    t_philo *phi = (t_philo *)philosopher;
    t_rules *rules = phi->rules;

    pthread_mutex_lock(&(rules->eating));
    phi->time_last_eat = timestamp();
    pthread_mutex_unlock(&(rules->eating));
    if (phi->philo_id % 2)
        usleep(500);
    while (!rules->died && !rules->all_ate)
    {
        if (rules->nb_philo == 1)
            philo_alone(phi);
        else
            philo_eats(phi);
        if (rules->died || rules->all_ate)
            break;
        print_moment(rules, phi->philo_id, "is sleeping");
        wait_time(rules, rules->time_sleep);
        print_moment(rules, phi->philo_id, "is thinking");
        usleep(100);
    }
    return NULL;
}

void death_seeker(t_rules *rules, t_philo *philos)
{
    int i;
    long long current_time;

    while (!rules->died && !rules->all_ate)
    {
        i = 0;
        while (i < rules->nb_philo && !rules->died)
        {
            current_time = timestamp();
            pthread_mutex_lock(&(rules->eating));
            if (time_taken(philos[i].time_last_eat, current_time) > rules->time_death)
            {
                print_moment(rules, philos[i].philo_id + 1, "died");
                rules->died = true;
                pthread_mutex_unlock(&(rules->eating));
                return;
            }
            pthread_mutex_unlock(&(rules->eating));
            i++;
            usleep(100);
        }
    }
}

void	finisher(t_rules *rules)
{
	int	i;

	i = -1;
	while (++i < rules->nb_philo)
		pthread_join(rules->philo[i].thread_id, NULL);
	i = -1;
	while (++i < rules->nb_philo)
		pthread_mutex_destroy(&rules->fork[i]);
	pthread_mutex_destroy(&rules->meal_count_mutex);
	pthread_mutex_destroy(&rules->write);
	pthread_mutex_destroy(&rules->eating);
}