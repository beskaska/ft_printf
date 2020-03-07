/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 16:30:25 by aimelda           #+#    #+#             */
/*   Updated: 2020/03/07 22:22:00 by aimelda          ###   ########.fr       */
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
	if (cur->argt == 'd' || cur->argt == 'i')
		return (to_signed_dec(cur, 10));
	else if (cur->argt == 'o')
		return (to_unsigned_num(cur, 8));
	else if (cur->argt == 'u')
		return (to_unsigned_num(cur, 10));
	else if (cur->argt == 'x' || cur->argt == 'X' || cur->argt == 'p')
		return (to_unsigned_hex(cur, *(unsigned long long*)cur->content, 16));
	else if (cur->argt == 'f')
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
