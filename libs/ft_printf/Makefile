# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/16 23:06:53 by rkedida           #+#    #+#              #
#    Updated: 2022/04/20 01:12:47 by rkedida          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS=	ft_decimal_hexafunction.c\
		ft_printf.c\

OBJS=$(SRCS:.c=.o)

CC = cc
CFLAG = -Wall -Wextra -Werror

all: $(NAME)

bonus: all

$(NAME) : $(OBJS)
	ar rcs $(NAME) $(OBJS)
	
%.o : %.c
	@$(CC) $(CFLAG) -c $^ -o $@ 
clean:
	@rm -f $(OBJS)

norm:
	@norminette *.c *.h

fclean: clean
	@rm -f $(NAME)

re: fclean all
.PHONY: all clean fclean re
