/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:22:33 by rkedida           #+#    #+#             */
/*   Updated: 2023/03/05 14:19:16 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_next_line(char *protect)
{
	int		i;
	char	*s;

	i = 0;
	if (!protect[i])
		return (NULL);
	while (protect[i] && protect[i] != '\n')
		i++;
	s = (char *)malloc((i + 2) * sizeof(char));
	if (!s)
		return (NULL);
	i = 0;
	while (protect[i] && protect[i] != '\n')
	{
		s[i] = protect[i];
		i++;
	}
	if (protect[i] == '\n')
	{
		s[i] = protect[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_protect(char *protect)
{
	int		i;
	int		j;
	char	*p;

	i = 0;
	while (protect[i] && protect[i] != '\n')
		i++;
	if (!protect[i])
	{
		free(protect);
		return (NULL);
	}
	p = (char *)malloc(sizeof(char) * (ft_strlen1(protect) - i + 1));
	if (!p)
		return (NULL);
	i++;
	j = 0;
	while (protect[i])
		p[j++] = protect[i++];
	p[j] = '\0';
	free(protect);
	return (p);
}

char	*ft_read_protect(int fd, char *protect)
{
	int		read_char;
	char	*buff;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	read_char = 1;
	while (!ft_strchr1(protect, '\n') && read_char != 0)
	{
		read_char = read(fd, buff, BUFFER_SIZE);
		if (read_char == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[read_char] = '\0';
		protect = ft_strjoin1(protect, buff);
	}
	free(buff);
	return (protect);
}

char	*get_next_line(int fd)
{
	static char	*protect;
	char		*l;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	protect = ft_read_protect(fd, protect);
	if (!protect)
		return (NULL);
	l = ft_next_line(protect);
	protect = ft_protect(protect);
	return (l);
}
