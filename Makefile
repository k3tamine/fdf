# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgonon <mgonon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/29 00:04:18 by mgonon            #+#    #+#              #
#    Updated: 2017/08/01 16:30:40 by mgonon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

# SRCS_NAME 	= 	main.c get_map.c display_map.c
# SRCS_PATH 	= 	srcs/
# SRCS 		= 	$(addprefix $(SRCS_PATH), $(SRCS_NAME))

# OBJS_NAME	= 	$(SRCS_NAME:.c=.o)
# OBJS_PATH	=	objs/
# OBJS		=	$(addprefix $(OBJS_PATH), $(OBJS_NAME))

SRCS = main.c get_map.c display_map.c
OBJS = $(SRCS:.c=.o)

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