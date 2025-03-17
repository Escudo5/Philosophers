NAME = philo
CC = cc

HEADERS = -I ./include

CFLAGS = -Wall -Werror -Wextra -g3  -pthread  -MMD -MP $(HEADERS)

SRCS:= $(addprefix src/, main.c life.c init.c utils.c parse.c )

OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS) $(DEPS)

fclean: clean
	rm -f $(NAME) 

re: fclean all

-include $(DEPS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re