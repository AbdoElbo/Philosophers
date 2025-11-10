# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/07 16:20:34 by aelbouaz          #+#    #+#              #
#    Updated: 2025/11/03 18:03:24 by aelbouaz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -pthread -g

PHILOS_SRCS = main.c error_handle.c initialisation.c helper_funcs_1.c

PHILOS_OBJ = $(PHILOS_SRCS:.c=.o)

NAME = philo

CC = cc

all: $(NAME)

$(NAME): $(PHILOS_OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(PHILOS_OBJ)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(PHILOS_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re test
