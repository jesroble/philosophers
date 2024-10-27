/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_punsigned.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesroble <jesroble@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 13:07:29 by jesroble          #+#    #+#             */
/*   Updated: 2024/10/22 16:41:55 by jesroble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_punsigned(unsigned int u)
{
	int	i;

	i = 0;
	if (u == 4294967295)
		i += write(1, "4294967295", 10);
	else if (u > 9)
	{
		i += ft_punsigned(u / 10);
		i += ft_pchar('0' + u % 10);
	}
	if (u > 0 && u <= 9)
		i += ft_pchar('0' + u % 10);
	return (i);
}
