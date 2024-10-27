/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesroble <jesroble@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:02:25 by jesroble          #+#    #+#             */
/*   Updated: 2024/01/03 15:51:20 by jesroble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdarg.h>
# include "ft_printf.h"

int	ft_printf(char const *str, ...);
int	ft_pchar(int c);
int	ft_pvoid(void *v);
int	ft_pstr(char *str);
int	ft_pnbr(int n);
int	ft_punsigned(unsigned int u);
int	ft_phex(unsigned int u, char const *str);

#endif