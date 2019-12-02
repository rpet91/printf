/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_conv_i.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 07:52:13 by rpet          #+#    #+#                 */
/*   Updated: 2019/11/28 18:19:27 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include "libftprintf.h"
#include "libft.h"
#include <stdio.h>

static char	*ft_fill_integer(int arg_int, int amount)
{
	int		i;
	char	*arg_str;

	i = 0;
	arg_str = malloc(sizeof(char) * (amount + 1));
	if (arg_str == NULL)
		return (NULL);
	if (arg_int < 0)
		arg_int = -arg_int;
	while (i < amount)
	{
		arg_str[amount - (i + 1)] = arg_int % 10 + '0';
		i++;
		arg_int = arg_int / 10;
	}
	return (arg_str);
}

static char	*ft_filling(char *str, char fill, int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		str[i] = fill;
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*ft_fill_string(char *str, t_flag *flag, int arg_int, int amount)
{
	int		i;
	int		size;
	char	*arg_str;
	int		sign;
	char	fill;

	i = 0;
	size = (flag->width > amount) ? flag->width : amount;
	sign = (arg_int < 0) ? '-' : flag->leading;
	fill = (flag->precision == -2 && flag->padding == 2) ? '0' : ' ';
	str = ft_filling(str, fill, size);
	arg_str = ft_fill_integer(arg_int, amount);
	if (sign != 0 && flag->padding == 0)
		str[size - amount] = sign;
	else if (sign != 0 && flag->padding != 0)
		str[i] = sign;
	while (i < amount - (0 < sign))
	{
		if (flag->padding == 1)
			str[i + (0 < sign)] = arg_str[i + (0 < sign)];
		else
			str[i + (0 < sign) + (size - amount)] = arg_str[i + (0 < sign)];
		i++;
	}
	return (str);
}

static int	ft_check_amount(t_flag *flag, int arg_int)
{
	int		amount;
	int		precision;
	int		width;

	precision = flag->precision;
	width = flag->width;
	amount = (arg_int < 0) ? ft_intlen(arg_int * -1) : ft_intlen(arg_int);
	amount = (amount < precision) ? precision : amount;
	if (flag->leading != 0 || arg_int < 0)
		amount++;
	return (amount);
}

t_list		*ft_conv_i(va_list args, t_flag *flag)
{
	char	*str;
	t_list	*new;
	int		arg_int;
	int		size;
	int		amount;

	if (flag->precision != -2 && flag->padding == 2)
		flag->padding = 0;
	arg_int = va_arg(args, int);
	amount = ft_check_amount(flag, arg_int);
	size = (flag->width > amount) ? flag->width : amount;
	str = malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (0);
	str = ft_fill_string(str, flag, arg_int, amount);
	new = ft_new_element(str, size);
	return (new);
}
