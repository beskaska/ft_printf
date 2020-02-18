/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 20:08:41 by aimelda           #+#    #+#             */
/*   Updated: 2020/02/18 20:21:48 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

int		main()
{
	int	d = 4563211;
	double g = 4563.646345701, gg = 1.258;
	char f = 1;
	int c = 92;
	char *p = "yes";
	int ans1, ans2;
	char	*str = "Test %2$+010x %1$+d %3$hhc %4$-010.5s %5$.3g %4$15.20p %1$#.3x!\n";

	ans1 = printf(str, f, d, c, p, g, gg);
	//ans2 = ft_printf(str, f, d, c, p, g, gg);
	//printf("%d vs. %d\n", ans1, ans2);
	printf("%lu\n", sizeof(long double));
}