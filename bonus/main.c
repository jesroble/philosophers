/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerope200 <jerope200@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:39:40 by jesroble          #+#    #+#             */
/*   Updated: 2024/10/30 17:38:39 by jerope200        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_rules	*rules;

	rules = malloc(sizeof(t_rules));
	if (ac != 5 && ac != 6)
		error_msg(USAGE);
	if ((!ft_init_rules(rules, av)))
		error_msg("threats could not be created");
	if ((!launcher(rules)))
		error_msg("something went wrong");
	exit(0);
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

void	error_msg(char *str)
{
	ft_printf(RED"Error"RESET": %s", str);
	exit (EXIT_FAILURE);
}