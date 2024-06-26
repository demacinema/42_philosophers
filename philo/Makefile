MAKEFLAGS += --no-print-directory

NAME	= philo

OBJ_DIR	= obj/
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g
# SAN 	= -fsanitize=address
SRC =	main.c \
		philo.c \
		philo_utils.c \
		threads.c \
		print.c

all: $(NAME)

OBJ = $(patsubst %.c, $(OBJ_DIR)%.o, $(SRC))

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $@

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f ./$(NAME)

re: fclean all

va:
		# valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=all ./philo
		# valgrind --leak-check=full --trace-children=yes env -i ./philo
		# valgrind --trace-children=yes --track-fds=all ./philo
		# valgrind --leak-check=full --trace-children=yes --track-fds=all ./philo
		valgrind --leak-check=full --trace-children=yes --suppressions=valgrind.supp  ./philo
		
.PHONY: all clean fclean re

LIGHT_RED = \033[1;31m
RED = \033[0;31m
DARK_RED = \033[0;35m
GREEN = \033[1;32m
YELLOW = \033[1;33m
LIGHT_CYAN = \033[1;36m
CYAN = \033[0;36m
LIGHT_BLUE = \033[1;34m
DARK_BLUE = \033[0;34m
DEFAULT = \033[0m