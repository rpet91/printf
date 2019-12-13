/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_conv_s.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 07:51:19 by rpet          #+#    #+#                 */
/*   Updated: 2019/12/13 17:43:50 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <wchar.h>
#include "libftprintf.h"
#include "libft.h"
#include <stdio.h>
#include <locale.h>

static unsigned char	*ft_create_str(unsigned char *str, wchar_t *arg_str,
				t_flag *flag, int amount)
{
	int			i;
	int			size;
	char		fill;
	wchar_t		*wstr;

	size = (amount < flag->width) ? flag->width : amount;
	fill = (flag->padding == 2) ? '0' : ' ';
	i = 0;
	wstr = malloc(sizeof(wchar_t) * (size + 1));
	if (wstr == NULL)
		return (NULL);
	wstr = ft_wfilling(wstr, fill, size);
	while (i < amount)
	{
		if (flag->padding == 1)
			wstr[i] = arg_str[i];
		else
			wstr[i + (size - amount)] = arg_str[i];
		i++;
	}
	wstr[size] = '\0';
	ft_wstr_to_str(wstr, str, size);
	free(wstr);
	return (str);
}

static int				ft_count_bytes_string(wchar_t *arg_str)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (arg_str[i] != '\0')
	{
		size += ft_count_bytes(arg_str[i]);
		i++;
	}
	return (size);
}

static wchar_t			*ft_check_modifier(va_list args, t_flag *flag)
{
	char		*convert_str;
	wchar_t		*arg_wstr;

	if (flag->modifier == 1)
	{
		arg_wstr = va_arg(args, wchar_t *);
		if (arg_wstr == NULL)
			arg_wstr = ft_str_to_wstr("(null)");
		else
			arg_wstr = ft_wstrdup(arg_wstr);
	}
	else
	{
		convert_str = va_arg(args, char *);
		if (convert_str == NULL)
			arg_wstr = ft_str_to_wstr("(null)");
		else
			arg_wstr = ft_str_to_wstr(convert_str);
	}
	return (arg_wstr);
}

int						ft_conv_s(va_list args, t_flag *flag)
{
	unsigned char	*str;
	wchar_t			*arg_str;
	int				size;
	int				amount;

	arg_str = ft_check_modifier(args, flag);
	amount = ft_count_bytes_string(arg_str);
	flag->precision = (flag->precision == -1) ? amount : flag->precision;
	amount = (amount < flag->precision) ? amount : flag->precision;
	size = (amount < flag->width) ? flag->width : amount;
	str = malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (0);
	str = ft_create_str(str, arg_str, flag, amount);
	write(1, str, size);
	free(str);
	return (size);
}
