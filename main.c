/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 20:08:41 by aimelda           #+#    #+#             */
/*   Updated: 2020/02/09 14:14:01 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

int		main()
{
	int	d = 4563211;
	int f = 33;

	printf("Test %2$+lld %1$d!\n", f, d);
	ft_printf("Test %2$+lld %1$d!\n", f, d);
}