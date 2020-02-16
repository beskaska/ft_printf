/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 19:26:23 by aimelda           #+#    #+#             */
/*   Updated: 2020/02/16 19:37:32 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		arg_malloc(t_args **args, t_printf *cur, int res)
{
	t_args	*tmp;

	if (args[res])
	{
		tmp = (t_args*)malloc(sizeof(t_args));
		tmp->next = args[res];
		args[res] = tmp;
	}
	else
	{
		args[res] = (t_args*)malloc(sizeof(t_args));
		args[res]->next = NULL;
		/*if (res > args[0]->arg_type)
			args[0]->arg_type = res;*/
	}
	args[res]->usedin = cur;
	//args[res]->arg_type = 1;
}

static void		arg_or_width(char **str, t_printf *cur, t_args **args)
{
	int		res;

	res = 0;
	while (ft_isdigit(**str))
		res = res * 10 + *((*str)++) - '0';
	if (res && **str == '$') //probably need to handle multiple using of an argument
	{
		arg_malloc(args, cur, res);
		//cur->arg_number = res; //--- here // NOT NEED
	}
	else
	{
		cur->width = res; //--- here
		cur->width_asterisk = 0; //--- here
		(*str)--;
	}
}

static void		get_precision(char **str, t_printf *cur, t_args **args)
{
	int		res;
	char	c;

	res = 0;
	c = 0;
	if (!ft_isdigit(*(++(*str))))
		c = *((*str)++);
	while (ft_isdigit(**str))
		res = res * 10 + *((*str)++) - '0';
	if (c == '*')
		if (res && **str == '$')
		{
			arg_malloc(args, cur, res);
			cur->precision_asterisk = res; //--- here
		}
		else
		{
			//cur->precision_asterisk = ++(args[0]->arg_type); //--- here
			(*str)--;
		}
	else
	{
		cur->precision_asterisk = 0;
		if (c != '-')
			cur->precision = res;
		(*str)--;
	}
}

static void		get_width(char **str, t_printf *cur, t_args **args)
{
	int		res;

	res = 0;
	while (ft_isdigit(*(++(*str))))
		res = res * 10 + **str - '0';
	if (res && **str == '$')
	{
		arg_malloc(args, cur, res);
		cur->width_asterisk = res; //--- here
	}
	else
	{
		//cur->width_asterisk = ++(args[0]->arg_type); //--- here
		(*str)--;
	}
}

void			ft_printf_parsing(char **format, t_printf *cur, t_args **args)
{
	while ((*format)++)
		if (**format >= '1' && **format <= '9')
			arg_or_width(format, cur, args);
		else if (**format == '+')
			cur->sign = '+';
		else if (**format == ' ')
			cur->space = ' ';
		else if (**format == '0')
			cur->zero = '0';
		else if (**format == '#')
			cur->sharp = 1;
		else if (**format == '-')
			cur->left_adjusted = 1;
		else if (**format == '.')
			get_precision(format, cur, args);
		else if (**format == '*')
			get_width(format, cur, args);
		else
			break;
	while (ft_strchr(PRINTF_FLAGS, **format))
		cur->arg_type *= *((*format)++);
	if (ft_strchr(CONVERSION_SPECIFIERS, **format))
		cur->arg_type *= **format;
	if (cur->left_adjusted && cur->zero == '0')
		cur->zero = ' ';
	if (!cur->sign)
		cur->sign = cur->space;
}
