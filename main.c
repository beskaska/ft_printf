/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 20:08:41 by aimelda           #+#    #+#             */
/*   Updated: 2020/02/13 21:30:19 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

int		main()
{
	int	d = 4563211;
	double g = 4563.646345701;
	int f = 0;
	int c = 92;
	char *p = "yes";
	int ans1, ans2;
	char	*str = "Test %2$+010x %1$+d %3$hhc %4$-010.5s %4$15.20p! %5$.3g\n";

	ans1 = printf(str, f, d, c, p, g);
	//ans2 = ft_printf(str, f, d);
	//printf("%d vs. %d\n", ans1, ans2);
}