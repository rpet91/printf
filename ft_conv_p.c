/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_conv_p.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 07:54:44 by rpet          #+#    #+#                 */
/*   Updated: 2019/12/05 15:01:46 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include "libftprintf.h"

static char		*ft_fill_unsigned(unsigned long long arg_int, int amount)
{
	int					i;
	unsigned long long	temp;
	char				*arg_str;

	i = 0;
	temp = arg_int;
	arg_str = malloc(sizeof(char) * (amount + 1));
	if (arg_str == NULL)
		return (NULL);
	while (i < amount)
	{
		temp = arg_int % 16;
		if (temp < 10)
			arg_str[amount - (i + 1)] = '0' + temp;
		else
			arg_str[amount - (i + 1)] = 'a' + temp - 10;
		arg_int = arg_int / 16;
		i++;
	}
	arg_str[i] = '\0';
	return (arg_str);
}

static char		*ft_create_s(char *str, t_flag *flag,
					unsigned long long arg_int, int amount)
{
	int		size;
	int		i;
	char	fill;
	char	*arg_str;

	size = (flag->width > amount) ? flag->width : amount;
	fill = (flag->padding == 2) ? '0' : ' ';
	str = ft_filling(str, fill, size);
	arg_str = ft_fill_unsigned(arg_int, amount);
	i = 0;
	arg_str[1] = 'x';
	while (i < amount)
	{
		if (flag->padding == 1)
			str[i] = arg_str[i];
		else
			str[i + (size - amount)] = arg_str[i];
		i++;
	}
	free(arg_str);
	return (str);
}

static int		ft_xll_len(unsigned long long arg_int)
{
	int		i;

	i = 0;
	if (arg_int == 0)
		return (1);
	while (arg_int != 0)
	{
		arg_int = arg_int / 16;
		i++;
	}
	return (i);
}

t_list			*ft_conv_p(va_list args, t_flag *flag)
{
	char				*str;
	t_list				*new;
	unsigned long long	arg_int;
	int					size;
	int					amount;

	arg_int = (unsigned long long)va_arg(args, void*);
	amount = ft_xll_len(arg_int) + 2;
	size = (flag->width > amount) ? flag->width : amount;
	str = malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (0);
	amount = (flag->padding == 2) ? size : amount;
	str = ft_create_s(str, flag, arg_int, amount);
	new = ft_new_element(str, size);
	flag->print_len += size;
	return (new);
}
