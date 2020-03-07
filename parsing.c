/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 19:26:23 by aimelda           #+#    #+#             */
/*   Updated: 2020/03/07 21:16:11 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		arg_malloc(t_args **args, t_printf *cur, int res, int *dst)
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

static void		arg_or_width(char **str, t_printf *cur, t_args **args)
{
	int		res;

	res = 0;
	while (ft_isdigit(**str))
		res = res * 10 + *((*str)++) - '0';
	if (res && **str == '$')
		arg_malloc(args, cur, res, &cur->arg_number);
	else
	{
		cur->width = res;
		cur->width_asterisk = 0;
		(*str)--;
	}
}

static void		get_precision(char **str, t_printf *cur, t_args **args, char c)
{
	int		res;

	res = 0;
	if (!ft_isdigit(*(++(*str))))
		c = *((*str)++);
	while (ft_isdigit(**str))
		res = res * 10 + *((*str)++) - '0';
	if (c == '*')
		if (res && **str == '$')
			arg_malloc(args, cur, res, &cur->precision_asterisk);
		else
		{
			--(*str);
			cur->precision = res;
			arg_malloc(args, cur, cur->arg_number++, &cur->precision_asterisk);
		}
	else
	{
		cur->precision_asterisk = 0;
		if (c != '-')
		{
			cur->precision = res;
			if (c)
				--(*str);
		}
		--(*str);
	}
}

static void		get_width(char **str, t_printf *cur, t_args **args)
{
	int		res;
	char	*tmp;

	res = 0;
	tmp = *str;
	while (ft_isdigit(*(++(*str))))
		res = res * 10 + **str - '0';
	if (res && **str == '$')
		arg_malloc(args, cur, res, &cur->width_asterisk);
	else
	{
		if (tmp != --(*str))
		{
			if (!res)
				cur->zero = '0';
			else
				cur->width = res;
		}
		arg_malloc(args, cur, cur->arg_number++, &cur->width_asterisk);
	}
}

void			ft_printf_parsing(char **format, t_printf *cur, t_args **args, int *max_arg)
{
	while (++(*format))
		if (**format >= '1' && **format <= '9')
			arg_or_width(format, cur, args);
		else if (**format == '+')
			cur->sign = '+';
		else if (**format == ' ')
		{
			if (!cur->sign)
				cur->sign = ' ';
		}
		else if (**format == '0')
			cur->zero = '0';
		else if (**format == '#')
			cur->sharp = 1;
		else if (**format == '-')
			cur->left_adjusted = 1;
		else if (**format == '.')
			get_precision(format, cur, args, 0);
		else if (**format == '*')
			get_width(format, cur, args);
		else
			break ;
	if (cur->left_adjusted)
		cur->zero = ' ';
	while (ft_strchr(PRINTF_FLAGS, **format))
		cur->argtype *= *((*format)++);
	if (ft_strchr(CONVERSION_SPECIFIERS, **format))
	{
		cur->argtype *= **format;
		if (!args[cur->arg_number])
			arg_malloc(args, cur, cur->arg_number, &cur->arg_number);
	}
	else if (**format == '%')
		cur->content = (void*)'%';
	else
		--(*format);
}
