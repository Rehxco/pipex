NAME = pipex

HEADER = pipex.h 

SOURCES = main.c \
		pipex.c \
		fork/fork.c \
		parsing/paths.c \
       	libft/ft_split.c \
	   	parsing/parsing.c \
	   	libft/utils_libft.c \
	   	libft/utils_libft_n_split.c \
	   	free/free_argv.c \
		free/free_struct.c



OBJECTS = $(SOURCES:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
