# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/13 23:20:17 by val               #+#    #+#              #
#    Updated: 2025/01/14 14:21:17 by vdurand          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
RESET = \033[0m
BG_GREEN = \033[42m

NAME = fdf

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
MLXFLAGS = -L$(MLX_DIR) -lmlx
FTFLAGS = -L$(LIBFT_DIR) -lft
LDFLAGS = -lXext -lm -lX11 $(MLXFLAGS) $(FTFLAGS)
INCLUDES = -I$(MLX_DIR) -I$(INC_DIR) -I$(LIBFT_DIR)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_DIR)/libft.a $(MLX_DIR)/libmlx.a
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "$(BG_GREEN)>>> Program $(NAME) compiled!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c Makefile $(INC_DIR)/*.h | $(OBJ_DIR)
	@echo "$(BLUE)>>> Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@echo "$(YELLOW)>>> Directory '$(OBJ_DIR)' created!$(RESET)"
	@mkdir -p $(OBJ_DIR)

$(LIBFT_DIR)/libft.a:
	@echo "$(BLUE)>>> Compiling Libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) > /dev/null 2>&1
	@$(MAKE) bonus -C $(LIBFT_DIR) > /dev/null 2>&1
	@echo "$(GREEN)>>> Compilation achieved!$(RESET)"

$(MLX_DIR)/libmlx.a:
	@echo "$(BLUE)>>> Configuration of MiniLibX...$(RESET)"
	@cd $(MLX_DIR) && bash configure > /dev/null 2>&1
	@echo "$(GREEN)>>> Configuration achieved!$(RESET)"

cleanlibs:
	@echo "$(YELLOW)>>> Cleaning libs...$(RESET)"
	@cd $(MLX_DIR)  && bash configure clean > /dev/null 2>&1
	@$(MAKE) fclean -C $(LIBFT_DIR) > /dev/null 2>&1

clean:
	@echo "$(YELLOW)>>> Cleaning objects$(RESET)"
	@rm -rf $(OBJ_DIR) > /dev/null 2>&1

fclean: clean cleanlibs
	@echo "$(YELLOW)>>> Cleaning executable...$(RESET)"
	@rm -f $(NAME) > /dev/null 2>&1

re: fclean all

.PHONY: all cleanlibs clean fclean re