/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pvoid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesroble <jesroble@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:58:26 by jesroble          #+#    #+#             */
/*   Updated: 2024/01/05 11:44:58 by jesroble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	voidlen(unsigned long long v)
{
	int	i;

	i = 0;
	while (v != 0)
	{
		v = v / 16;
		i++;
	}
	return (i);
}

void	write_void(unsigned long long v)
{
	if (v >= 16)
	{
		write_void(v / 16);
	}
	if (v % 16 <= 9)
	{
		ft_pchar('0' + v % 16);
	}
	else
		ft_pchar((v % 16) - 10 + 'a');
}

int	ft_pvoid(void *ptr)
{
	unsigned long long	v;
	int					i;

	i = 0;
	if (ptr == NULL)
		i++;
	v = (unsigned long long) ptr;
	write(1, "0x", 2);
	i += 2;
	i += voidlen(v);
	if (v != 0)
		write_void(v);
	else
	{
		write(1, "0", 1);
	}
	return (i);
}
