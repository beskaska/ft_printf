/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 16:30:25 by aimelda           #+#    #+#             */
/*   Updated: 2020/02/09 08:33:32 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	converting(t_args **args, va_list *ap)
{
	int		i;

	i = 0;
	while (++i <= *(int*)(args[0]->content))
	{
		if (args[i]->usedin->arg_type % 'd' == 0)
		{
			args[i]->content = malloc(sizeof(char));
			*(char*)(args[i]->content) = va_arg(*ap, char);
		}
		else if (args[i]->usedin->arg_type % 'h' == 0)
		{
			args[i]->content = malloc(sizeof(short int));
			*(short int*)(args[i]->content) = va_arg(*ap, short int);
		}
	}
	
}

int		ft_printf_print(t_printf *cur, t_args **args, va_list ap)
{
	int		sum;

	sum = 0;
	while (cur)
	{
		sum += cur->text_length;
		while (cur->text_length--)
			ft_putchar(*cur->text++);
		

		//free;
	}
	return (sum);
}
