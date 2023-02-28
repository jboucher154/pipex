# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/07 15:33:41 by jebouche          #+#    #+#              #
#    Updated: 2023/02/28 12:55:34 by jebouche         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

LIB = libft/libft.a

OBJ_DIR = obj

SRCS = main.c pathfinding.c children.c cleanup.c this_is_awkward.c

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

DEPS = pipex.h

CC = cc

CFLAGS = -Wall -Wextra -Werror -I. -Ilibft/includes

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) $(DEBUG) $(OBJS) $(LIB) -o $(NAME)

$(OBJ_DIR)/%.o:%.c $(DEPS)
	$(CC) $(CFLAGS) $(DEBUG) -c $< -o $@

$(LIB):
	$(MAKE) -C libft

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean: 
	rm -f $(OBJS)
	$(MAKE) clean -C libft

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C libft

re: fclean all

.PHONY: all clean fclean re

.SILENT:
