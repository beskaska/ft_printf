/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 20:08:41 by aimelda           #+#    #+#             */
/*   Updated: 2020/02/10 22:01:07 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

int		main()
{
	int	d = 4563211;
	int f = 33;
	int ans1, ans2;

	ans1 = printf("Test %2$+lld %1$d!\n", f, d);
	ans2 = ft_printf("Test %2$+lld %1$d!\n", f, d);
	printf("%d vs. %d\n", ans1, ans2);
}