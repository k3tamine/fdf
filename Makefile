# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgonon <mgonon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/29 00:04:18 by mgonon            #+#    #+#              #
#    Updated: 2017/07/21 01:29:27 by mgonon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

OPTION = -c

SRC = main.c get_map.c display_map.c

OBJ = $(SRC:.c=.o)

FLAGS = -Werror -Wall -Wextra

FRAWK = -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJ)
	make -C minilibx/
	make -C libft/
	gcc $(FLAGS) -o $(NAME) $(OBJ) -L libft -lft -L minilibx $(FRAWK)

clean:
	make -C minilibx/ clean
	make -C libft/ clean
	/bin/rm -f $(OBJ)

fclean: clean
	make -C libft/ fclean
	/bin/rm -f $(NAME)

re: fclean all