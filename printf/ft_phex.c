/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_phex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesroble <jesroble@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 16:20:47 by jesroble          #+#    #+#             */
/*   Updated: 2024/01/05 11:42:21 by jesroble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	numlen(unsigned int u)
{
	int	i;

	i = 0;
	while (u != 0)
	{
		u = u / 16;
		i++;
	}
	return (i);
}

void	write_hex(unsigned int u, char const *str)
{
	if (u >= 16)
	{
		write_hex(u / 16, str);
	}
	if (u % 16 <= 9)
	{
		ft_pchar('0' + (u % 16));
	}
	else
	{
		if (*str == 'x')
			ft_pchar((u % 16) - 10 + 'a');
		if (*str == 'X')
			ft_pchar((u % 16) - 10 + 'A');
	}
}

int	ft_phex(unsigned int u, char const *str)
{
	int	i;

	i = numlen(u);
	if (u == 0)
	{
		ft_pchar('0' + u);
		i++;
	}
	else
		write_hex(u, str);
	return (i);
}
