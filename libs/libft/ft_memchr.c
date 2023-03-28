/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 08:28:42 by rkedida           #+#    #+#             */
/*   Updated: 2022/04/01 13:33:44 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*dst;
	unsigned char		search;
	size_t				count;

	dst = (const unsigned char *)s;
	search = (unsigned char )c;
	count = 0;
	while (count < n)
	{
		if (*dst == search)
			return ((void *)dst);
		dst++;
		count++;
	}
	return (0);
}
