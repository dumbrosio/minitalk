/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vd-ambro <vd-ambro@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:32:27 by vd-ambro          #+#    #+#             */
/*   Updated: 2023/07/12 14:35:21 by vd-ambro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

int	print_char(int c)
{
	write(1, &c, 1);
	return (1);
}

int	print_str(char *str)
{
	int	i;

	if (!str)
	{
		str = "(null)";
		i = 6;
	}
	i = 0;
	while (str[i])
	{
		print_char(str[i]);
		i++;
	}
	return (i);
}

int	print_nbr(int n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		if (n == -2147483648)
		{
			print_str("-2147483648");
			return (11);
		}
		i += print_char('-');
		n = -n;
	}
	if (n > 9)
		i += print_nbr(n / 10);
	i += print_char(n % 10 + 48);
	return (i);
}

int	handle_case(va_list args, const char c)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += print_char(va_arg(args, int));
	else if (c == 's')
		count += print_str(va_arg(args, char *));
	else if (c == 'd' || c == 'i')
		count += print_nbr(va_arg(args, int));
	else if (c == '%')
		count += print_char('%');
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list args;
	int i;
	int count;

	if (!format)
		return (0);
	i = 0;
	count = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			count += handle_case(args, format[i]);
		}
		else
			count += print_char(format[i]);
		i++;
	}
	va_end(args);
	return (count);
}