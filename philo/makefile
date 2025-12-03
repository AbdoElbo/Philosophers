# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/07 16:20:34 by aelbouaz          #+#    #+#              #
#    Updated: 2025/12/02 20:22:28 by aelbouaz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -pthread -g -fsanitize=thread

PHILOS_SRCS = src/main.c src/error_handle.c src/initialisation.c \
		src/utils_1.c src/utils_2.c src/utils_3.c src/routine_1.c \
		src/routine_2.c

PHILOS_OBJ = $(PHILOS_SRCS:.c=.o)

HEADERS	:= -I ./include

NAME = philo

CC = cc

all: $(NAME)

$(NAME): $(PHILOS_OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(PHILOS_OBJ)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	rm -f $(PHILOS_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re test
