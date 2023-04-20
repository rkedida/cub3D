# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sheali <sheali@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/26 23:22:24 by rkedida           #+#    #+#              #
#    Updated: 2023/04/21 01:32:38 by sheali           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	cub3D

SRC				=	$(SRC_DIR)/main.c\
					$(SRC_DIR)/parsing.c\
					$(SRC_DIR)/player_position.c\
					$(SRC_DIR)/handle_direction.c\
					$(SRC_DIR)/load_configuration_file.c\
					$(SRC_DIR)/validate_map.c\
					$(SRC_DIR)/dfs_search.c\
					$(SRC_DIR)/error.c\
					$(SRC_DIR)/moves.c\
					$(SRC_DIR)/init.c\
					$(SRC_DIR)/surrounded_walls.c\
					$(SRC_DIR)/textures.c\
					$(SRC_DIR)/key_hook_manager.c\
					$(SRC_DIR)/compass_direction.c\
					$(SRC_DIR)/parsing_config_info.c\
					$(SRC_DIR)/raycasting.c\
					$(SRC_DIR)/raycasting_ii.c\
					$(SRC_DIR)/raycasting_iii.c\
					

SRC_DIR			=	./src
MAPS_DIR		=	./maps
INC_DIR			=	./includes
TEXTURES_DIR	=	./textures
MLX_DIR			=	./libs/mlx
LIBFT_DIR		=	./libs/libft
GNL_DIR			=	./libs/get_next_line
FTPRINTF_DIR	=	./libs/ft_printf
OBJ_DIR			=	./obj

HEADERS			=	$(INC_DIR)/so_long.h\
					$(LIBFT_DIR)/libft.h\
					$(GNl_DIR)/get_next_line.h\
					$(FTPRINTF_DIR)/ft_printf.h

INCLUDES		=	-I$(INC_DIR) -I$(MLX_DIR) -I$(LIBFT_DIR) -I$(GNL_DIR) -I$(FTPRINTF_DIR)

OBJ				=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror

MLX_LIB			=	-L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
LIBFT_LIB		=	$(LIBFT_DIR)/libft.a
GNL_LIB			=	$(GNL_DIR)/get_next_line.a
FTPRINTF_LIB	=	$(FTPRINTF_DIR)/libftprintf.a


all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
 
$(NAME): $(OBJ)
	@make -C $(MLX_DIR) > /dev/null 2>&1
	@make -C $(LIBFT_DIR) > /dev/null 2>&1
	@make -C $(GNL_DIR) > /dev/null 2>&1
	@make -C $(FTPRINTF_DIR) > /dev/null 2>&1
	@$(CC) $(CFLAGS) $(OBJ) $(MLX_LIB) $(LIBFT_LIB) $(GNL_LIB) $(FTPRINTF_LIB) -o $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

norm:
	norminette src/ includes/ libs/ft_printf libs/libft libs/get_next_line

clean:
	-@$(RM) $(OBJ) --silent
	-@$(RM)  -rf $(OBJ_DIR) --silent
	@make clean -C $(MLX_DIR)
	@make clean -C $(LIBFT_DIR) --silent
	@make clean -C $(GNL_DIR) --silent
	@make clean -C $(FTPRINTF_DIR) --silent

fclean: clean
	-@$(RM) $(NAME) --silent
	@make fclean -C $(LIBFT_DIR) --silent
	@make fclean -C $(GNL_DIR) --silent
	@make fclean -C $(FTPRINTF_DIR) --silent

re: fclean all

.PHONY: re, fclean, clean, all