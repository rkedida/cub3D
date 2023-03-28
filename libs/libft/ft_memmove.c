/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 13:40:21 by rkedida           #+#    #+#             */
/*   Updated: 2022/04/01 13:37:17 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	count;
	char	*d;
	char	*s;

	count = 0;
	d = (char *)dst;
	s = (char *)src;
	if (!d && !s)
		return (NULL);
	if (d > s)
		while (len-- > 0)
			d[len] = s[len];
	else
	{
		while (count < len)
		{
			d[count] = s[count];
			count++;
		}
	}
	return ((void *)dst);
}
