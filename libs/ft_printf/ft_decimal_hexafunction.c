/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decimal_hexafunction.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 05:17:27 by rkedida           #+#    #+#             */
/*   Updated: 2022/07/27 21:32:50 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int nbr)
{
	int	x;

	x = 0;
	if (nbr == -2147483648)
	{
		x += ft_putstr("-2");
		nbr = 147483648;
	}
	if (nbr < 0)
	{
		x += ft_putchar('-');
		nbr = -nbr;
	}
	if (nbr >= 10)
	{
		x += ft_putnbr(nbr / 10);
		x += ft_putnbr(nbr % 10);
	}
	if (nbr < 10)
		x += ft_putchar(nbr + 48);
	return (x);
}

int	ft_hexadecimal(unsigned long long hex, char x)
{
	int	z;

	z = 0;
	if (hex < 10)
		z += ft_putchar(hex + 48);
	else if (hex < 16)
	{
		if (x == 'x')
			z += ft_putchar(hex + 87);
		if (x == 'X')
			z += ft_putchar(hex + 55);
	}
	else
	{
		z += ft_hexadecimal(hex / 16, x);
		z += ft_hexadecimal(hex % 16, x);
	}
	return (z);
}

int	ft_unsigned_ten(unsigned int base)
{
	int	i;

	i = 0;
	if (base < 10)
		i += ft_putchar(base + 48);
	else
	{
		i += ft_putnbr(base / 10);
		i += ft_putnbr(base % 10);
	}
	return (i);
}

int	ft_putstr(char const *s)
{
	int	x;

	x = 0;
	if (!s)
		s = "(null)";
	while (s[x] != '\0')
	{
		x += ft_putchar(s[x]);
	}
	return (x);
}

int	ft_unsigned_address(unsigned long long address)
{
	int	i;

	i = 0;
	if (address < 10)
		i += ft_putchar(address + 48);
	else if (address < 16)
		i += ft_putchar(address + 87);
	else
	{
		i += ft_unsigned_address(address / 16);
		i += ft_unsigned_address(address % 16);
	}
	return (i);
}
