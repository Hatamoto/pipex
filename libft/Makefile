# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/28 20:09:48 by mburakow          #+#    #+#              #
#    Updated: 2024/02/28 12:54:31 by mburakow         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	libft.a

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -I
DEBUG_FLAGS 	= 	-g
SRC_DIR			= 	./ft_printf/srcs
INCLUDE			= 	./ft_printf/incs
SRCS			= 	ft_printf.c			ft_print_addr.c		ft_print_char.c	\
					ft_print_string.c	ft_print_hex.c		ft_print_uint.c	\
					ft_print_int.c
OBJ_DIR			=	./ft_printf/objs
OBJS			=	$(SRCS:%.c=$(OBJ_DIR)/%.o)
LIBFT_DIR		=	./libft
LIBFT			=	$(LIBFT_DIR)/libft.a

all:				$(NAME)

bonus:				all

debug: 				CFLAGS += $(DEBUG_FLAGS)
debug: 				bonus

$(NAME):			$(LIBFT) $(OBJ_DIR) $(OBJS)
					cp	$(LIBFT) $(NAME)
					ar -crs $(NAME) $(OBJS)

$(OBJ_DIR)/%.o:		$(SRC_DIR)/%.c
					$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(LIBFT):
					make -C $(LIBFT_DIR) bonus all

$(OBJ_DIR):
					mkdir -p $(OBJ_DIR)

clean:
					rm -rf $(OBJ_DIR)

fclean:				clean
					rm -f $(NAME)
					rm -f $(LIBFT)

re:					fclean all

.PHONY:				all bonus clean fclean re libft debug
