/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 01:12:48 by rkedida           #+#    #+#             */
/*   Updated: 2023/03/03 17:12:05 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int	ft_unsigned_address(unsigned long long address);
int	ft_putstr(char const *s);
int	ft_unsigned_ten(unsigned int base);
int	ft_hexadecimal(unsigned long long hex, char x);
int	ft_putnbr(int nbr);
int	ft_putchar(char c);
int	ft_check_specifier(char str, va_list specifier);
int	ft_printf(const char *s, ...);

#endif