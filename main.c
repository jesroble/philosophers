/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesroble <jesroble@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:39:40 by jesroble          #+#    #+#             */
/*   Updated: 2024/10/25 11:48:06 by jesroble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	error_msg(char *str)
{
	ft_printf(RED"Error"RESET": %s", str);
	exit (EXIT_FAILURE);
}

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
