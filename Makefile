# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/07 15:33:41 by jebouche          #+#    #+#              #
#    Updated: 2023/02/24 16:36:14 by jebouche         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/07 15:33:41 by jebouche          #+#    #+#              #
#    Updated: 2023/02/24 16:01:52 by jebouche         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

LIB = libft/libft.a

# SRC_DIR = src/

OBJ_DIR = obj

SRCS = main.c pathfinding.c children.c cleanup.c

OBJS = $(SRCS:.c=.o)

OBJS_PATH = $(addprefix $(OBJ_DIR)/, $(OBJS))

DEPS = pipex.h

CC = cc

CFLAGS = -Wall -Wextra -Werror -I. -Ilibft/includes

DEBUG = -g3

DEBUG_SANI = -g -fsanitize=address

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJS) $(LIB)
	@$(CC) $(CFLAGS) $(DEBUG) $(OBJS) $(LIB) -o $(NAME)

$(OBJS_PATH): $(OBJ_DIR)/%.o:%.c $(DEPS)
	@$(CC) $(CFLAGS) $(DEBUG) -c $< -o $@

$(LIB):
	@$(MAKE) -C libft

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

clean: 
	@rm -f $(OBJS)
	@$(MAKE) clean -C libft

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C libft

re : fclean all

.PHONY: all clean fclean re

.SILENT:

# NAME = pipex

# LIB = libft/libft.a

# SRCS = main.c pathfinding.c children.c cleanup.c

# OBJS = $(SRCS:.c=.o)

# DEPS = pipex.h

# CC = cc

# CFLAGS = -Wall -Wextra -Werror -I. -Ilibft/includes

# DEBUG = -g3

# DEBUG_SANI = -g -fsanitize=address

# all: $(NAME)

# $(NAME): $(OBJS) $(LIB)
# 	@$(CC) $(CFLAGS) $(DEBUG) $(OBJS) $(LIB) -o $(NAME)

# %.o : %.c $(DEPS)
# 	@$(CC) $(CFLAGS) $(DEBUG) -c $< -o $@

# $(LIB):
# 	@$(MAKE) -C libft

# clean: 
# 	@rm -f $(OBJS)
# 	@$(MAKE) clean -C libft

# fclean: clean
# 	@rm -f $(NAME)
# 	@$(MAKE) fclean -C libft

# re : fclean all

# .PHONY: all clean fclean re