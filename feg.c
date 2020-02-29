/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 21:34:49 by aimelda           #+#    #+#             */
/*   Updated: 2020/02/29 18:45:12 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*num_to_txt(unsigned long long n, int exp, int *len)
{
	int		nb;
	char	*txt;

	*len = MAX_LLONG_DIGIT;
	if (*(unsigned long long*)(txt) < 10000000000000000000UL)
		--(*len);
	txt = (char*)malloc(*len + ft_abs(exp) + 1);
	if (exp > 0)
		nb = *len + ft_abs(exp);
	else
		nb = *len;
	txt[nb--] = '\0';
	while (n)
	{
		txt[nb--] = n % 10 + '0';
		n = n / 10;
	}
	return (txt);
}

static void	rounding(char **num, int start, int *len)
{
	char	flag;
	int		i;

	i = start;
	flag = 0;
	if ((*num)[i] - '0' > 5)
		flag = 1;
	else if ((*num)[i] - '0' == 5)
		while ((*num)[++i])
			if ((*num)[i] > '0')
			{
				flag = 1;
				break;
			}
	if (flag)
	{
		while ((*num)[--start] - '0' + 1 == 10)
			(*num)[start] = '0';
		(*num)[start] = (*num)[start] - '0' + 1 + '0';
		if (start < 0)
		{
			++(*len);
			--(*num);
		}
	}
}

static char	*divide(char *num, int *len, int exp, int precision)
{
	int		i;
	char	oida;
	char	tmp;

	while (exp++)//optimize by division 2^64
	{
		i = 0;
		oida = 0;
		while (num[i])
		{
			tmp = num[i];
			num[i] = (num[i] - '0') / 2 + oida + '0';
			if (tmp % 2)
				oida = 5;
			else
				oida = 0;
			i++;
		}
		if (oida)
		{
			num[i] = '5';
			num[i + 1] = '\0';
		}
		if (num[0] == '0')
		{
			--(*len);
			num++;
		}
	}
	if (i - (oida == 0) - *len > precision && precision + len >= 0)
		rounding(&num, precision + *len, len);
	return (num);
}

/*static char	*divide(char *num, int *len, int exp)
{
	unsigned long long	b;
	unsigned long long	oida;
	int					i;

	b = 256UL * 256 * 256 * 16;
	oida = 0;
	while (exp)
	{
		exp += 28;
		while (exp > 0)
		{
			exp--;
			b /= 2;
		}
		i = 0;
		while (num[i] || oida)
		{
			if (!num[i])
				num[i + 1] = '\0';
			num[i] = (oida += num[i] - '0') / b + '0';
			printf("%c\n", num[i]);
			oida = (oida - (num[i++] - '0') * b) * 10;
			if (num[0] == '0')
			{
				--(*len);
				num++;
				i--;
			}		
		}
	}
	return (num);
}*/

static char *multiply(char *num, int *len, int exp)
{
	unsigned long long	b;
	unsigned long long	oida;
	int					i;

	b = 256UL * 256 * 256 * 16;//determine and define
	oida = 0;
	while (exp)//determine and define
	{
		exp -= 28;
		while (exp < 0)
		{
			exp++;
			b /= 2;
		}
		i = *len;
		while (i--)
		{
			oida += (num[i] - '0') * b;
			num[i] = oida % 10 + '0';
			oida /= 10;
		}
		while (oida)
		{
			++(*len);
			*(--num) = oida % 10 + '0';
			oida /= 10;
		}
	}
	return (num);
}

static char	*get_number(t_printf *cur, char *txt, int *exp, int *len)
{
	if ((*exp = *(short*)(txt + 8)) < 0)
		*exp = (short)*exp ^ (short)-32768;
	if (*exp == 32767)
	{
		*len = 3;
		*exp = 0;
		if (*(unsigned long long*)(txt) == MAX_ULLONG)
			txt = ft_strdup("inf");
		else
		{
			txt = ft_strdup("nan");
			cur->sign = 0;
		}
		cur->zero = ' ';
		cur->sharp = 0;
		cur->precision = 0;
		return (txt);
	}
	else if (!*exp && !(*(unsigned long long*)(txt)))
	{
		*len = 1;
		return (txt = ft_strdup("0"));
	}
	else
		*exp = *exp - EXPONENT_BIAS - (sizeof(long long) * 8 - 1);
	return (num_to_txt(*(unsigned long long*)(txt), *exp, len));
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
	int		tmp;
	char	*txt;
	char	*index;

	if (((char*)cur->content)[9] < 0)
		cur->sign = '-';
	txt = get_number(cur, (char*)cur->content, &tmp, &len);
	if (tmp >= 0)
		index = multiply(txt + tmp, &len, tmp);
	else
		index = divide(txt, &len, tmp, cur->precision);
	tmp = cur->precision + (cur->sign > 0) + (cur->precision || cur->sharp);
	if (len > 0)
		tmp += len;
	else
		tmp += 1;
	if (!(cur->left_adjusted))
		while (cur->width > tmp++)
			ft_putchar(cur->zero);
	ft_putchar(cur->sign);
	put_float(cur, index, len);
	if (cur->left_adjusted)
		while (cur->width > tmp++)
			ft_putchar(cur->zero);
	free(cur->content);
	free(txt);
	return (tmp - 1);
}
