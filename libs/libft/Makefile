# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: val <val@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/15 21:41:19 by val               #+#    #+#              #
#    Updated: 2025/01/15 21:43:33 by val              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror
CC = gcc
NAME = libft.a

BASE_SRC = ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strlen.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putptr_fd.c \
		ft_putnbr_base_fd.c \
		ft_printf.c \
		get_next_line.c \
		ft_strend.c

BONUS_SRC = ft_lstadd_back_bonus.c \
			ft_lstadd_front_bonus.c \
			ft_lstclear_bonus.c \
			ft_lstdelone_bonus.c \
			ft_lstiter_bonus.c \
			ft_lstlast_bonus.c \
			ft_lstmap_bonus.c \
			ft_lstnew_bonus.c \
			ft_lstsize_bonus.c

BASE_OBJS = $(BASE_SRC:.c=.o)
BONUS_OBJS = $(BONUS_SRC:.c=.o)
ALL_OBJS = $(BASE_OBJS) $(BONUS_OBJS)

all: $(NAME) 

bonus: .bonus

.bonus : $(ALL_OBJS)
	ar rcs $(NAME) $(ALL_OBJS)
	@touch .bonus

$(NAME): $(BASE_OBJS)
	ar rcs $(NAME) $(BASE_OBJS)

%.o: %.c $(INCLUDE_DIR) Makefile
	$(CC) $(CFLAGS) -o $@ -c $< 

clean:
	rm -rf $(BONUS_OBJS) $(BASE_OBJS)
	@rm -rf .bonus

fclean: clean
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re bonus
