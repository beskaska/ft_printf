/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_malloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 21:43:10 by aimelda           #+#    #+#             */
/*   Updated: 2020/08/23 18:55:30 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		free_args(t_args *to_del)
{
	t_args	*tmp;

	while (to_del)
	{
		tmp = to_del;
		to_del = to_del->next;
		free(tmp);
	}
}

int			free_all(t_args **args)
{
	int		i;

	i = 0;
	while (++i < MAX_PRINTF_ARG)
		if (args[i])
			free_args(args[i]);
	return (-1);
}

int			arg_malloc(t_args **args, t_printf *cur, int res, int *dst)
{
	t_args	*tmp;

	if (args[res])
	{
		if (!(tmp = (t_args*)malloc(sizeof(t_args))))
			return (free_all(args));
		tmp->next = args[res];
		args[res] = tmp;
	}
	else
	{
		if (!(args[res] = (t_args*)malloc(sizeof(t_args))))
			return (free_all(args));
		args[res]->next = NULL;
	}
	args[res]->usedin = cur;
	*dst = res;
	return (0);
}
