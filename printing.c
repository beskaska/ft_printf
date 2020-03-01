/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 16:30:25 by aimelda           #+#    #+#             */
/*   Updated: 2020/03/01 20:06:59 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_printf	*free_printf(t_printf *to_del)
{
	t_printf	*tmp;

	tmp = to_del->next;
	free(to_del);
	return (tmp);
}

static int		converting(t_printf *cur)
{
	if (cur->arg_type == 'd' || cur->arg_type == 'i')
		return (to_signed_dec(cur, 10));
	else if (cur->arg_type == 'o')
		return (to_unsigned_num(cur, 8));
	else if (cur->arg_type == 'u')
		return (to_unsigned_num(cur, 10));
	else if (cur->arg_type == 'x' || cur->arg_type == 'X')
	{
		return (to_unsigned_hex(cur, *(unsigned long long*)cur->content, 16));
		free(cur->content); //looks not good
	}
	else if (cur->arg_type == 'f')
		return (to_float(cur, *(long double*)cur->content));
	else
		return (to_csp(cur));
}

int				ft_printf_print(t_printf *cur)
{
	int		sum;

	sum = 0;
	while (cur)
	{
		sum += cur->text_length;
		while (cur->text_length--)
			ft_putchar(*cur->text++);
		if (cur->content)
			sum += converting(cur);
		cur = free_printf(cur);
	}
	return (sum);
}
