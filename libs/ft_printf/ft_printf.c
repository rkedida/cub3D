/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 00:33:04 by rkedida           #+#    #+#             */
/*   Updated: 2022/07/27 21:37:49 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_check_specifier(char str, va_list specifier)
{
	int	len;

	len = 0;
	if (str == 'c')
		len += ft_putchar(va_arg(specifier, int));
	else if (str == 's')
		len += ft_putstr(va_arg(specifier, char *));
	else if (str == 'd')
		len += ft_putnbr(va_arg(specifier, int));
	else if (str == 'i')
		len += ft_putnbr(va_arg(specifier, unsigned long long));
	else if (str == 'x' || str == 'X')
		len += ft_hexadecimal(va_arg(specifier, unsigned int), str);
	else if (str == 'u')
		len += ft_unsigned_ten(va_arg(specifier, unsigned int));
	else if (str == '%')
		len += ft_putchar('%');
	else if (str == 'p')
	{
		len += ft_putstr("0x");
		len += ft_unsigned_address(va_arg(specifier, unsigned long long));
	}
	return (len);
}

int	ft_printf(const char *s, ...)
{
	va_list	specifier;
	int		len;
	int		i;

	va_start(specifier, s);
	len = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '%')
		{
			i++;
			len += ft_check_specifier(s[i], specifier);
			i++;
		}
		else
		{
			len += ft_putchar(s[i]);
			i++;
		}
	}
	va_end(specifier);
	return (len);
}
