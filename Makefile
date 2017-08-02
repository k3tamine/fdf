# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgonon <mgonon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/29 00:04:18 by mgonon            #+#    #+#              #
#    Updated: 2017/08/02 13:08:40 by mgonon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRCS = main.c get_map.c display_map.c handle_img.c
OBJS = $(addprefix srcs/, $(SRCS:.c=.o))

FLAGS = -Werror -Wall -Wextra

FRAWK = -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJS)
	make -C minilibx/
	make -C libft/
	gcc $(FLAGS) -o $(NAME) $(OBJS) -Llibft -lft -Lminilibx -lmlx $(FRAWK)	

clean:
	make -C minilibx/ clean
	make -C libft/ clean
	/bin/rm -f $(OBJS)

fclean: clean
	make -C libft/ fclean
	/bin/rm -f $(NAME)

re: fclean all