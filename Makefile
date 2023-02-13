# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/07 15:33:41 by jebouche          #+#    #+#              #
#    Updated: 2023/02/13 10:27:48 by jebouche         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

LIB = libft/libft.a

SRCS = main.c test.c

OBJS = $(SRCS:.c=.o)

DEPS = pipex.h

CC = cc

CFLAGS = -Wall -Wextra -Werror -I. -Ilibft/includes

DEBUG = -g

DEBUG_SANI = -g -fsanitize=address

all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	@$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $(NAME)

%.o : %.c $(DEPS)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIB):
	@$(MAKE) -C libft

clean: 
	@rm -f $(OBJS)
	@$(MAKE) clean -C libft

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C libft

re : fclean all

.PHONY: all clean fclean re