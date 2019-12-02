/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_check_flag.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/15 16:24:44 by rpet          #+#    #+#                 */
/*   Updated: 2019/11/27 14:29:01 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libftprintf.h"
#include "libft.h"
#include <stdio.h>

/*
** padding = 0 --> default, didn't find a - and 0
** padding = 1 --> found a -
** padding = 2 --> found a 0 and not a -
** leading = 0 --> default, didn't find a space and a +
** leading = 1 --> found a +
** leading = 2 --> found a space and not a + and -
** hash = 0 --> didn't find a #
** hash = 1 --> found a #
** width = 0 --> didn't find a * or number(int)
** width = -1 --> found a *
** width = number --> found a number
** precision = -1 --> found a . and no number or *
** precision = -2 --> didn't find a .
** precision = number --> found a . and number or *
** modifier = 0 --> didn't find l/ll/h/hh
** modifier = 1 --> found l
** modifier = 2 --> found ll
** modifier = 3 --> found h
** modifier = 4 --> found hh
*/

int			ft_check_modifier(char *form_str, t_flag *new)
{
	if (*form_str == 'l' && *(form_str + 1) != 'l')
	{
		new->modifier = 1;
		new->flag_len = new->flag_len + 1;
		return (1);
	}
	if (*form_str == 'l' && *(form_str + 1) == 'l')
	{
		new->modifier = 2;
		new->flag_len = new->flag_len + 2;
		return (2);
	}
	if (*form_str == 'h' && *(form_str + 1) != 'h')
	{
		new->modifier = 3;
		new->flag_len = new->flag_len + 1;
		return (1);
	}
	if (*form_str == 'h' && *(form_str + 1) == 'h')
	{
		new->modifier = 4;
		new->flag_len = new->flag_len + 2;
		return (2);
	}
	return (0);
}

int			ft_check_precision(va_list args, char *form_str, t_flag *new)
{
	int		i;

	i = 1;
	if (form_str[i] != '*' && ft_isdigit(form_str[(int)i]) == 0)
		new->precision = -1;
	if (form_str[i] == '*')
	{
		new->precision = va_arg(args, int);
		return (2);
	}
	while (ft_isdigit(form_str[(int)i]) == 1 && form_str != '\0')
	{
		new->precision = new->precision * 10 + form_str[i] - '0';
		i++;
	}
	new->flag_len = new->flag_len + i;
	return (i);
}

int			ft_check_width(va_list args, char *form_str, t_flag *new)
{
	int		i;

	i = 0;
	if (*form_str == '*')
	{
		new->width = va_arg(args, int);
		i = 1;
	}
	if (*form_str >= '1' && *form_str <= '9')
	{
		new->width = ft_atoi(form_str);
		i = ft_intlen(new->width);
	}
	new->flag_len = new->flag_len + i;
	return (i);
}

int			ft_check_flags(char *form_str, t_flag *new)
{
	int		i;

	i = 0;
	while (ft_strchr("-0+ #", form_str[i]))
	{
		if (form_str[i] == '-')
			new->padding = 1;
		if (form_str[i] == '0' && new->padding != 1)
			new->padding = 2;
		if (form_str[i] == '+')
			new->leading = '+';
		if (form_str[i] == ' ' && new->leading != '+' && new->padding != 1)
			new->leading = ' ';
		if (form_str[i] == '#')
			new->hash = 1;
		i++;
	}
	new->flag_len = i;
	return (i);
}

t_flag		*ft_check_flag(va_list args, char *form_str)
{
	t_flag		*new;
	int			str_i;

	new = ft_empty_flag();
	str_i = ft_check_flags(form_str, new);
	form_str = form_str + str_i;
	str_i = ft_check_width(args, form_str, new);
	form_str = form_str + str_i;
	if (*form_str == '.')
	{
		str_i = ft_check_precision(args, form_str, new);
		form_str = form_str + str_i;
	}
	else
		new->precision = -2;
	str_i = ft_check_modifier(form_str, new);
	form_str = form_str + str_i;
	new->conversion = *form_str;
	return (new);
}
