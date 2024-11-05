/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesroble <jesroble@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 22:05:23 by jesroble          #+#    #+#             */
/*   Updated: 2024/10/27 21:00:17 by jesroble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned int	fruit_generator(unsigned long time, int id)
{
	long	seed;

	seed = (time ^ (long)id) * 48271;
	if (seed < 0)
		seed *= -1;
	return (seed);
}

unsigned long	my_rand(unsigned long fruit)
{
	unsigned long	a;
	unsigned long	c;
	unsigned long	m;

	a = 1103515245;
	c = 12345;
	m = 2147483648;
	fruit = (a * fruit + c) % m;
	return (fruit);
}
