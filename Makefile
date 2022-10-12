# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nphilipp <nphilipp@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/09/30 20:09:28 by nphilipp      #+#    #+#                  #
#    Updated: 2022/10/12 19:42:11 by nphilipp      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRCS = src/philo.c src/setup.c src/print.c src/Activities.c src/alive.c
FLAGS = -pthread -Wall -Werror -Wextra
all: $(NAME)

$(NAME): $(SRCAS)
	gcc $(FLAGS) $(SRCS) -o $(NAME)

clean: 

fclean: clean
	rm -f $(NAME)

re: fclean all