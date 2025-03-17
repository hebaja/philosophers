CC=cc
CC_FLAGS=-Wall -Wextra -Werror
NAME=libphilo.a
EXEC_NAME=philo
INC_DIR=include
SRC_DIR=src
SRC_FILES=init_table.c input_validation.c main.c monitor.c philo_actions.c philo_build.c philo_routine.c utils.c
SRCS=$(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS=$(SRCS:.c=.o)

all: $(NAME)
	$(CC) $(CC_FLAGS) -pthread -o $(EXEC_NAME) -L. -lphilo -I$(INC_DIR)

$(NAME): $(OBJS)
	ar rcs $@ $(OBJS)

.c.o:
	$(CC) $(CC_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f $(EXEC_NAME)

re: fclean all

.PHONY: all clean fclean re
