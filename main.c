/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 20:08:41 by aimelda           #+#    #+#             */
/*   Updated: 2020/02/29 19:15:55 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"
#include "float.h"

int		main()
{
	int	d = 4563211;
	long double g = 0, gg = 1.258, fg = 5751235121000L;
	char f = 1;
	int c = 92;
	char *p = "yes";
	int ans1, ans2 = 9550;
	//char	*str = "Test %2$+010x %1$+d %3c %4$-010.5s %6f %5$.3g %4$15.20p %1$#.3x!\n";
	char	*str = "Test %2$+010x %1$+d %3c!\n";
	//char *str = "Test %+#10.50Lf!\n";

	ans1 = printf(str, d, ans2, c);
	ans2 = ft_printf(str, d, ans2, c);
	printf("%d vs. %d\n", ans1, ans2);
	//printf("%lu\n", sizeof(double));
}