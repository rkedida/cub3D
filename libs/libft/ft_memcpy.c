/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 13:21:13 by rkedida           #+#    #+#             */
/*   Updated: 2022/04/01 13:36:18 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned const char	*csrc;
	unsigned char		*cdst;
	size_t				temp;

	csrc = (unsigned char *)src;
	cdst = (unsigned char *)dst;
	temp = 0;
	if (!dst && !src)
		return (NULL);
	while (temp < n)
	{
		cdst[temp] = csrc[temp];
		temp++;
	}
	return (cdst);
}
