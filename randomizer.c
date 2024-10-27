/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesroble <jesroble@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 22:05:23 by jesroble          #+#    #+#             */
/*   Updated: 2024/10/26 22:17:49 by jesroble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned int	fruit_generator(unsigned long time, int id)
{
	long	i;

	i = (long)id;
	
}

unsigned int	my_rand(unsigned int fruit)
{
	unsigned int	a;
	unsigned int	c;
	unsigned int	m;

	a = 1103515245;
	c = 12345;
	m = 2147483648;
	fruit = (a * fruit + c) % m;
	return (fruit);
}
