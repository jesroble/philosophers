/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pnbr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesroble <jesroble@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 13:09:53 by jesroble          #+#    #+#             */
/*   Updated: 2024/01/05 11:24:23 by jesroble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printnbr(int n)
{
	if (n == -2147483648)
		write(1, "-2147483648", 11);
	else if (n < 0)
	{
		n = n * -1;
		write(1, "-", 1);
	}
	if (n >= 0 && n <= 9)
	{
		ft_pchar('0' + n % 10);
	}
	if (n > 9)
	{
		ft_pnbr(n / 10);
		ft_pchar('0' + n % 10);
	}
}

int	ft_pnbr(int n)
{
	int	i;

	ft_printnbr(n);
	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}
