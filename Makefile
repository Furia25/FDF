# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: val <val@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/13 23:20:17 by val               #+#    #+#              #
#    Updated: 2025/01/14 00:29:29 by val              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom de l'exécutable
NAME = wireframe

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes
LIBFT_DIR = libs/libft
MLX_DIR = libs/minilibx-linux

SRC = $(shell find $(SRC_DIR) -type f -name "*.c")
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

CC = gcc
OPTIFLAGS = -O3
CFLAGS = $(OPTIFLAGS) -Werror -Wextra -Wall
LDFLAGS = -lXext -lm -lX11 -L$(MLX_DIR) -lmlx -L$(LIBFT_DIR) -lft
INCLUDES = -I$(MLX_DIR) -I$(INC_DIR) -I$(LIBFT_DIR)

# Règle principale
all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_DIR)/libft.a $(MLX_DIR)/libmlx.a
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) bonus -C $(LIBFT_DIR)

$(MLX_DIR)/libmlx.a:
	cd $(MLX_DIR) && bash configure

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	cd $(MLX_DIR) && bash configure clean
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re