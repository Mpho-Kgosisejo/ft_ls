# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkgosise <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/28 14:59:51 by mkgosise          #+#    #+#              #
#    Updated: 2017/09/05 10:55:42 by mkgosise         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

RAWSRC = main.c\
		 prepare_list.c\
		 recursive_handler.c\
		 display_handler.c\
		 sort_handler.c\
		 display_helper.c\
		 ft_precision.c\
		 recursive_helper.c

SRC = $(RAWSRC:%=src/%)

OBJ = $(SRC:src/%.c=%.o)

LIBFT = ./libft

FLAGS = -Wall\
		-Wextra\
		-Werror

all: $(NAME)

$(NAME):
	@make -C $(LIBFT)
	@gcc -c $(FLAGS) $(SRC)
	gcc -o $(NAME) $(FLAGS) $(OBJ) -L$(LIBFT) -lft

clean:
	rm -f $(OBJ)
	@cd ./libft && $(MAKE) clean

fclean: clean
	rm -f $(NAME)
	@cd ./libft && $(MAKE) fclean

re: fclean all
