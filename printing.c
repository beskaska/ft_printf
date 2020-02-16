/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 16:30:25 by aimelda           #+#    #+#             */
/*   Updated: 2020/02/15 20:59:12 by aimelda          ###   ########.fr       */
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

static void		converting(t_printf *cur)
{
	if (cur->arg_type == 'd' || cur->arg_type == 'i' || cur->arg_type == 'o'
	|| cur->arg_type == 'u' || cur->arg_type == 'x' || cur->arg_type == 'X')
		to_diouxX(cur);
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
		{
			//converting;
			ft_putstr(cur->arg_text);
			sum += cur->arg_length;
			free(cur->arg_text);
		}
		cur = free_printf(cur);
	}
	return (sum);
}
