# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggiertzu <ggiertzu@student.42berlin.d      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/22 19:51:00 by ggiertzu          #+#    #+#              #
#    Updated: 2024/01/13 01:09:42 by ggiertzu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= push_swap
CFLAGS	:= -g -O0 -Wall -Werror -Wextra #-fdump-rtl-expand
CC		:= gcc
LIBFT_D	:= ./libft
LIBFT_L	:= libftprintf.a
LIBFT	:= $(LIBFT_D)/$(LIBFT_L)

HEADERS	:= -I $(LIBFT_D) -I .
LIBS	:= $(LIBFT)
SRCS	:= $(wildcard ps_utils*.c) ps_main.c
OBJS	:= ${SRCS:.c=.o}

all: $(NAME)

bonus: all

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_D)
clean:
	rm -rf $(OBJS)
	make clean -C $(LIBFT_D)
fclean: clean
	rm -rf $(NAME)
	make fclean -C $(LIBFT_D)
re: clean all

.PHONY: all, clean, fclean, re, libmlx
