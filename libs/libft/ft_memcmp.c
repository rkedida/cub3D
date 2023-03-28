/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 10:58:53 by rkedida           #+#    #+#             */
/*   Updated: 2022/04/01 13:35:27 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*lens1;
	unsigned char	*lens2;
	int				result;

	lens1 = (unsigned char *)s1;
	lens2 = (unsigned char *)s2;
	result = 0;
	while (n--)
	{
		if (lens1[result] != lens2[result])
			return (lens1[result] - lens2[result]);
		result++;
	}
	return (0);
}
