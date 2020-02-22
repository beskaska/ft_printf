/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 21:22:45 by aimelda           #+#    #+#             */
/*   Updated: 2020/02/22 22:53:18 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	to_unsigned_char(t_printf *cur)
{
	if (!(cur->left_adjusted))
		while (cur->width-- > 1)
			ft_putchar(cur->zero);
	ft_putchar(*(unsigned char*)(cur->content));
	if (cur->left_adjusted)
		while (cur->width-- > 1)
			ft_putchar(cur->zero);
	free(cur->content);
	return (1);
}

static int	to_str_pointer(t_printf *cur, char *str)
{
	int		len;

	len = ft_strlen(cur->content);
	if (!(cur->left_adjusted))
		while (cur->width > len++)
			ft_putchar(cur->zero);
	if (cur->precision)
		while (cur->precision-- && *str)
			ft_putchar(*str++);
	else
		ft_putstr(str);
	if (cur->left_adjusted)
		while (cur->width > len++)
			ft_putchar(cur->zero);
	return (len);
}

int			to_csp(t_printf *cur)
{
	if (cur->arg_type == 'c')
		return (to_unsigned_char(cur));
	else if (cur->arg_type == 's')
		return (to_str_pointer(cur, cur->content));
	else if (cur->arg_type == 'p')
	{
		cur->sharp = 1;
		cur->arg_type = 'x';
		return (to_unsigned_hex(*(unsigned long long*)cur->content, cur, 16));
	}
	return (0);
}
