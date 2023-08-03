# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/10 05:13:54 by dinunes-          #+#    #+#              #
#    Updated: 2023/08/02 12:28:05 by dinunes-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Program name
NAME = minishell

# Compiler
CC = cc
CFLAGS = -Werror -Wextra -Wall

# Libft
LIBFT_PATH	= libft/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)

# Includes
INC = -I ./inc/

# Sources and Objects paths
SRC_PATH = src/
OBJ_PATH = obj/

# Sources
SRC = $(addprefix $(SRC_PATH), main.c parsing.c builtins.c path.c utils.c signals.c parsing_utils.c env.c heredoc.c)

# Objects
OBJ = $(SRC:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c | $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(LIBFT):
	@make -sC $(LIBFT_PATH)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(LIBFT_PATH) -lft -lreadline
	@echo "\033[0;91m$(NAME) \033[0;0mready."

clean:
	@rm -rf $(OBJ_PATH)
	@make clean -sC $(LIBFT_PATH)

fclean: clean
	@rm -f $(NAME)
	@make fclean -sC $(LIBFT_PATH)
	@echo "\033[0;91m$(NAME) \033[0;0mfile removed."

re: fclean all

.PHONY: all re clean fclean
