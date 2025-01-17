/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 19:38:58 by aimelda           #+#    #+#             */
/*   Updated: 2020/03/09 16:56:02 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	sasha4(char *num, unsigned long long *oida,
					int i, unsigned long long b)
{
	if (!num[i])
	{
		num[i + 1] = '\0';
		num[i] = '0';
	}
	num[i] = (*oida += num[i] - '0') / b;
	*oida = (*oida - num[i] * b) * 10;
	num[i] += '0';
}

static void	sasha5(int *exp, unsigned long long *b, int flag)
{
	if (flag)
	{
		*exp += 32;
		while (*exp > 0)
		{
			(*exp)--;
			*b /= 2;
		}
	}
	else
	{
		*exp -= 32;
		while (*exp < 0)
		{
			(*exp)++;
			*b /= 2;
		}
	}
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
				break ;
			}
	if (flag)
	{
		while ((*num)[--start] - '0' + 1 == 10)
			(*num)[start] = '0';
		++((*num)[start]);
		if (start < 0)
		{
			++(*len);
			--(*num);
		}
	}
}

char		*ft_printf_multiply(char *num, int *len, int exp)
{
	unsigned long long	b;
	unsigned long long	oida;
	int					i;

	b = 256UL * 256 * 256 * 256;
	oida = 0;
	while (exp)
	{
		sasha5(&exp, &b, 0);
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

char		*ft_printf_divide(char *num, int *len, int exp, int precision)
{
	unsigned long long	b;
	unsigned long long	oida;
	int					i;

	b = 256UL * 256 * 256 * 256;
	oida = 0;
	while (exp)
	{
		sasha5(&exp, &b, 1);
		i = 0;
		while (num[i] || oida)
		{
			sasha4(num, &oida, i, b);
			if (*num == '0')
			{
				--(*len);
				num++;
			}
			else
				i++;
		}
	}
	if (i - (oida == 0) - *len > precision && precision + len >= 0)
		rounding(&num, precision + *len, len);
	return (num);
}
