# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/23 18:04:37 by mburakow          #+#    #+#              #
#    Updated: 2024/05/05 13:01:21 by mburakow         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	pipex
CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
DEBUG_FLAGS 	= 	-g
SRC_DIR			= 	./srcs
INC_DIRS		= 	./incs ./libft/libft ./libft/ft_printf/incs
INCLUDE 		=	$(foreach dir, $(INC_DIRS), -I $(dir))
SRCS			= 	pipex.c			utils.c			error.c	\
					handler.c		quotes.c		quote_utils.c
BONUS_SRCS		=	pipex_bonus.c	utils_bonus.c	error_bonus.c	\
					handler_bonus.c	quotes_bonus.c	quote_utils_bonus.c
OBJ_DIR			=	objs
OBJS			=	$(SRCS:%.c=$(OBJ_DIR)/%.o)
BONUS_OBJS		=	$(BONUS_SRCS:%.c=$(OBJ_DIR)/%.o)
LIBFT_DIR		=	./libft
LIBFT			=	$(LIBFT_DIR)/libft.a

$(OBJ_DIR)/%.o:		$(SRC_DIR)/%.c
					$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

all:				$(NAME)

bonus:				$(LIBFT) $(OBJ_DIR) $(BONUS_OBJS)
					$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) -o $(NAME)

debug: 				CFLAGS += $(DEBUG_FLAGS)
debug:				all

$(NAME):			$(LIBFT) $(OBJ_DIR) $(OBJS)
					$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
					make -C $(LIBFT_DIR) all

$(OBJ_DIR):
					mkdir -p $(OBJ_DIR)

clean:
					make -C $(LIBFT_DIR) clean
					rm -rf $(OBJ_DIR)

fclean:				clean
					rm -f $(NAME)
					rm -f $(LIBFT)

re:					fclean all

.PHONY:				all bonus clean fclean re libft
