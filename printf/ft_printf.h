/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerope200 <jerope200@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:02:25 by jesroble          #+#    #+#             */
/*   Updated: 2024/11/05 11:19:26 by jerope200        ###   ########.fr       */
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