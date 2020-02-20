/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 21:34:49 by aimelda           #+#    #+#             */
/*   Updated: 2020/02/20 20:47:04 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*get_number(t_printf *cur, char *txt, int *len)
{
	char	*num;

	
	return (num);
}

int			to_f(t_printf *cur, long double n)
{
	int		len;
	int		tmp;
	char	*txt;

	if ((char)cur->content < 0)
		cur->sign = '-';
	txt = get_number(cur, (char*)cur->content, &len);
	tmp = len + cur->precision + cur->sign > 0;
	if (!(cur->left_adjusted))
		while (cur->width > tmp++)
			ft_putchar(cur->zero);
	ft_putchar(cur->sign);
	ft_putstr(txt);
	if (cur->left_adjusted)
		while (cur->width > tmp++)
			ft_putchar(cur->zero);
	free(cur->content);
	return (tmp - 1);
}

int			to_feg(t_printf *cur)
{
	long double	tmp;

	if (!(cur->arg_type % 'f'))
		;//
	else if (!(cur->arg_type % 'e'))
		;//
	else
		;//
}
