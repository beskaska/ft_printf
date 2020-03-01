/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 21:22:45 by aimelda           #+#    #+#             */
/*   Updated: 2020/03/01 18:58:11 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	to_unsigned_char(t_printf *cur)
{
	int		tmp;

	tmp = 1;
	if (!(cur->left_adjusted))
		while (cur->width > tmp++)
			ft_putchar(cur->zero);
	if (cur->arg_type == 1)
		ft_putchar('%');
	else
	{
		ft_putchar(*(unsigned char*)(cur->content));
		free(cur->content);
	}
	if (cur->left_adjusted)
		while (cur->width > tmp++)
			ft_putchar(cur->zero);
	return (tmp - 1);
}

static int	to_str_pointer(t_printf *cur, char *str)
{
	int		len;
	int		tmp;

	if (cur->precision_asterisk == -1)
		len = ft_strlen(str);
	else
		len = ft_min(ft_strlen(str), cur->precision);
	tmp = len;
	if (!(cur->left_adjusted))
		while (cur->width > tmp++)
			ft_putchar(cur->zero);
	if (!cur->precision_asterisk)
		while (len--)
			ft_putchar(*str++);
	else
		ft_putstr(str);
	if (cur->left_adjusted)
		while (cur->width > tmp++)
			ft_putchar(cur->zero);
	if (!ft_strcmp(str, "(null)"))
		free(str);
	return (tmp - 1);
}

int			to_csp(t_printf *cur)
{
	if (cur->arg_type == 'c' || cur->arg_type == 1)
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
