/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 19:04:19 by rkedida           #+#    #+#             */
/*   Updated: 2023/03/05 14:20:34 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen1(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr1(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen1(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin1(char *s, char *buff)
{
	size_t	i;
	size_t	j;
	char	*s1;

	if (!s)
	{
		s = (char *)malloc(1 * sizeof(char));
		s[0] = '\0';
	}
	if (!buff || !s)
		return (NULL);
	s1 = malloc((ft_strlen1(s) + ft_strlen1(buff) + 1) * sizeof(char));
	if (s1 == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (s)
		while (s[++i] != '\0')
			s1[i] = s[i];
	while (buff[j] != '\0')
		s1[i++] = buff[j++];
	s1[ft_strlen1(s) + ft_strlen1(buff)] = '\0';
	free(s);
	return (s1);
}
