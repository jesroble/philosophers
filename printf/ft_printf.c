/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesroble <jesroble@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:36:47 by jesroble          #+#    #+#             */
/*   Updated: 2024/02/18 17:54:47 by jesroble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	next_arg(va_list args, char const *str)
{
	int				i;
	unsigned int	u;

	i = 0;
	if (*str == 'c')
		i += ft_pchar(va_arg(args, int));
	else if (*str == 's')
		i += ft_pstr(va_arg(args, char *));
	else if (*str == 'p')
		i += ft_pvoid(va_arg(args, void *));
	else if (*str == 'd')
		i += ft_pnbr(va_arg(args, int));
	else if (*str == 'i')
		i += ft_pnbr(va_arg(args, int));
	else if (*str == 'u')
		i += ft_punsigned(va_arg(args, unsigned int));
	else if (*str == 'X' || *str == 'x')
	{
		u = va_arg(args, unsigned int);
		i += ft_phex(u, str);
	}
	else if (*str == '%')
		i += ft_pchar(*str);
	return (i);
}

int	ft_printf(char const *format, ...)
{
	va_list	args;
	int		i;

	if (write(1, "", 0) == -1)
		return (-1);
	va_start(args, format);
	i = 0;
	while (*format != '\0')
	{
		if (*format == '%')
			i += next_arg(args, ++format);
		else
		{
			write(1, format, 1);
			i++;
		}
		format++;
	}
	va_end(args);
	return (i);
}

/* int	main(void)
{
	ft_printf("Hello, %x\n", -200);
    printf("Hello, %x", -200);
	return (0);
} */

/* gcc ft_pchar.c ft_phex.c ft_pnbr.c 
ft_printf.c ft_pstr.c ft_punsigned.c ft_pvoid.c */