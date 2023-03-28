/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:17:20 by rkedida           #+#    #+#             */
/*   Updated: 2022/04/03 19:03:11 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	nlen(int n)
{
	size_t	len;

	if (n == 0)
		return (1);
	len = 0;
	if (n < 0)
		len++;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	size_t	len;
	size_t	i;
	char	*result;

	len = nlen(n);
	result = malloc((sizeof (char) * len + 1));
	if (!result)
		return (NULL);
	result[len] = '\0';
	if (n < 0)
	{
		result[0] = '-';
		i = 1;
	}
	else
		i = 0;
	while (len-- > i)
	{
		if (n < 0)
			result[len] = '0' + n % 10 * (-1);
		else
			result[len] = '0' + n % 10;
		n = n / 10;
	}
	return (result);
}
