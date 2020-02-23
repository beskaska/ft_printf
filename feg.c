/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 21:34:49 by aimelda           #+#    #+#             */
/*   Updated: 2020/02/23 21:37:06 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*num_to_txt(unsigned long long n)
{
	int		nb;//int
	char	*txt;

	txt = ft_strnew(MAX_LLONG_DIGIT);
	nb = MAX_LLONG_DIGIT - 1;
	while (n)
	{
		txt[nb--] = n % 10 + '0';
		n = n / 10;
	}
	return (txt);
}

static char	*multiply(char *num, int *len, int exp)
{
	char	offset;
	char	i;
	char	oida;
	char	tmp;

	if (exp < 0)
		while (exp++) //optimize by comparing the precision and len
		{
			if (num[0] == '1')
			{
				offset = 1;
				--(*len);
			}
			else
				offset = 0;
			i = 0;
			oida = 0;
			while (i < MAX_LLONG_DIGIT)
			{
				tmp = num[i];
				if (i >= offset)
					num[i - offset] = (num[i] - '0') / 2 + oida + '0';
				if (tmp % 2)
					oida = 5;
				else
					oida = 0;
				i++;
			}

		}
	return (num);
}

static char	*get_number(t_printf *cur, char *txt, int *len)
{
	char	*num_txt;
	short	exp;

	//if special values: +0; -0; NaN; +infinity; -infinity
	if ((exp = *(short*)(txt + 8)) < 0)
		exp = exp ^ (short)-32768;
	exp -= 16383 + sizeof(long long) * 8 - 1;
	num_txt = num_to_txt(*(unsigned long long*)(txt));
	*len = MAX_LLONG_DIGIT; //maybe should init in main function
	return (multiply(num_txt, len, exp));
}

static void	put_float(t_printf *cur, char *txt, int len)
{
	if (len > 0)
	{
		while (len && *txt)
		{
			len--;
			ft_putchar(*txt++);
		}
		while (len--)
			ft_putchar('0');
		len++;
	}
	else
		ft_putchar('0');
	if (cur->precision || cur->sharp)
		ft_putchar('.');
	while(cur->precision && *txt)
	{
		cur->precision--;
		if (++len > 0)
			ft_putchar(*txt++);
		else
			ft_putchar('0');
	}
	while (cur->precision--)
		ft_putchar('0');
}

int			to_float(t_printf *cur, long double n)
{
	int		len;
	//int		len_frac;
	int		tmp;
	char	*txt;

	if (((char*)cur->content)[9] < 0)
		cur->sign = '-';
	txt = get_number(cur, (char*)cur->content, &len);
	tmp = len + cur->precision + cur->sign > 0 + (cur->precision || cur->sharp); //one char for dec point?
	if (!(cur->left_adjusted))
		while (cur->width > tmp++)
			ft_putchar(cur->zero);
	ft_putchar(cur->sign);
	put_float(cur, txt, len);
	if (cur->left_adjusted)
		while (cur->width > tmp++)
			ft_putchar(cur->zero);
	free(cur->content);
	free(txt);
	return (tmp - 1);
}
