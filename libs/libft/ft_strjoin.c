/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:55:12 by rkedida           #+#    #+#             */
/*   Updated: 2022/04/01 13:42:47 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	index;
	char			*dst;

	index = 0;
	if (s1 == 0 || s2 == 0)
		return (0);
	dst = malloc(sizeof(*dst) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (dst == 0)
		return (0);
	while (*s1 != '\0')
		dst[index++] = *s1++;
	while (*s2 != '\0')
		dst[index++] = *s2++;
	dst[index] = '\0';
	return (dst);
}
