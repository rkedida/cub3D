/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 18:32:02 by rkedida           #+#    #+#             */
/*   Updated: 2023/03/05 14:18:45 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlen1(const char *s);
char	*ft_strchr1(const char *s, int c);
char	*get_next_line(int fd);
char	*ft_strjoin1(char *s, char *buff);
char	*ft_next_line(char *protect);
char	*ft_protect(char *protect);
char	*ft_read_protect(int fd, char *protect);

#endif 
