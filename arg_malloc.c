/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_malloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 21:43:10 by aimelda           #+#    #+#             */
/*   Updated: 2020/03/07 23:13:14 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		arg_malloc(t_args **args, t_printf *cur, int res, int *dst)
{
	t_args	*tmp;

	if (args[res])
	{
		tmp = (t_args*)malloc(sizeof(t_args));//if NULL
		tmp->next = args[res];
		args[res] = tmp;
	}
	else
	{
		args[res] = (t_args*)malloc(sizeof(t_args));//if NULL
		args[res]->next = NULL;
	}
	args[res]->usedin = cur;
	*dst = res;
}

void		free_args(t_args *to_del)
{
	t_args	*tmp;

	while (to_del->next)
	{
		tmp = to_del->next;
		tmp->usedin->content = to_del->usedin->content;
		free(to_del);
		to_del = tmp;
	}
	free(to_del);
}
